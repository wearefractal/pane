#include "WebKitWindow.h"
#include <stdio.h>

using namespace v8;
using namespace node;

Persistent<FunctionTemplate> WebKitWindow::s_ct;
Persistent<String> WebKitWindow::emit_symbol;

void WebKitWindow::Initialize(Handle<Object> target) {
    HandleScope scope;

    emit_symbol = NODE_PSYMBOL("emit");

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(NODE_SYMBOL("WebKitWindow"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "close", Close);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "open", Open);
    //TODO: Implement these
    NODE_SET_PROTOTYPE_METHOD(s_ct, "reload", Reload);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "move", Move);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "setMaximized", SetMaximized);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "setFullscreen", SetFullscreen);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "setUrl", SetUrl);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "getUrl", GetUrl);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "setHtml", SetHtml);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "execute", ExecuteScript);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "setSize", SetSize);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "getSize", GetSize);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "setResizable", SetResizable);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "getResizable", GetResizable);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "setTitle", SetTitle);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "getTitle", GetTitle);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "getFocused", GetFocused);

    target->Set(NODE_SYMBOL("WebKitWindow"), t->GetFunction());
}

Handle<Value> WebKitWindow::New (const Arguments& args)
{
    HandleScope scope;
    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(NODE_SYMBOL("Use the new operator to create instances of this object.")));
    }

    //Initialize glib threading support and libgtk
    gtk_init(NULL, NULL);

    WebKitWindow *window = new WebKitWindow;
    window->Wrap(args.This());

    //Create UI components
    window->window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    window->view_ = webkit_web_view_new();

    //Connect signals from UI components to JS events
    g_signal_connect(window->window_, "destroy", G_CALLBACK(window->Destroy), window);
    g_signal_connect(window->view_, "console-message", G_CALLBACK(window->ConsoleMessage), window);
    g_signal_connect(window->view_, "notify::title", G_CALLBACK(window->RefreshTitle), window);

    //Add components to window
    gtk_container_add(GTK_CONTAINER(window->window_), window->view_);
    gtk_widget_show_all(window->window_);
    return scope.Close(args.This());
}

/* FUNCTIONS */

Handle<Value> WebKitWindow::Open(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    run_loop();
    window->Emit("open", 0, NULL);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Close(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    window->Emit("close", 0, NULL);
    quit_loop();
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Reload(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    webkit_web_view_reload(WEBKIT_WEB_VIEW(window->view_));
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Move(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_UINT32(0, x);
    ARG_CHECK_UINT32(1, y);
    int x = args[0]->Int32Value();
    int y = args[1]->Int32Value();
    gtk_window_move(GTK_WINDOW(window->window_), x, y);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::SetMaximized(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_BOOL(0, maximized);
    bool maximized = args[0]->BooleanValue();
    if(maximized){
        gtk_window_maximize(GTK_WINDOW(window->window_));
    } else {
        gtk_window_unmaximize(GTK_WINDOW(window->window_));
    }
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::SetFullscreen(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_BOOL(0, fullscreen);
    bool fullscreen = args[0]->BooleanValue();
    if(fullscreen){
        gtk_window_fullscreen(GTK_WINDOW(window->window_));
    } else {
        gtk_window_unfullscreen(GTK_WINDOW(window->window_));
    }
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::SetTitle(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_STRING(0, title);
    String::Utf8Value title(args[0]->ToString());
    gtk_window_set_title(GTK_WINDOW(window->window_), *title);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetTitle(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    const gchar *title = gtk_window_get_title(GTK_WINDOW(window->window_));
    if(!title){
        return scope.Close(Null());
    }
    return scope.Close(NODE_SYMBOL(title));
}
Handle<Value> WebKitWindow::SetUrl(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    ARG_CHECK_STRING(0, url);
    String::Utf8Value url(args[0]->ToString());
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(window->view_), *url);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetUrl(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    const gchar *uri = webkit_web_view_get_uri(WEBKIT_WEB_VIEW(window->view_));
    if (!uri){
        return scope.Close(Null());
    }
    return scope.Close(NODE_SYMBOL(uri));
}
Handle<Value> WebKitWindow::SetHtml(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    ARG_CHECK_STRING(0, html);
    String::Utf8Value html(args[0]->ToString());
    webkit_web_view_load_string(WEBKIT_WEB_VIEW(window->view_), *html, NULL, NULL, NULL);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::ExecuteScript(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    ARG_CHECK_STRING(0, script);
    String::Utf8Value script(args[0]->ToString());
    webkit_web_view_execute_script(WEBKIT_WEB_VIEW(window->view_), *script);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::SetSize(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_UINT32(0, height);
    ARG_CHECK_UINT32(1, width);
    gtk_window_set_default_size(GTK_WINDOW(window->window_), args[1]->Int32Value(), args[0]->Int32Value());
    gtk_window_resize(GTK_WINDOW(window->window_), args[1]->Int32Value(), args[0]->Int32Value());
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetSize(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    int height;
    int width;
    GtkWindow *win = GTK_WINDOW(window->window_);
    gtk_window_get_size(win, &width, &height);
    printf("hay\n");
    if (!height|| !width){
        return scope.Close(Null());
    }
    printf("size: %ix%i", height, width);
    Handle<Array> array = Array::New(2);
    if (array.IsEmpty()){
        return Handle<Array>();
    }
    array->Set(0, NODE_CONSTANT(height));
    array->Set(1, NODE_CONSTANT(width));
    return scope.Close(array);
}
Handle<Value> WebKitWindow::SetResizable(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_BOOL(0, resizable);
    gtk_window_set_resizable(GTK_WINDOW(window->window_), args[0]->BooleanValue());
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetResizable(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    bool resizable = gtk_window_has_toplevel_focus(GTK_WINDOW(window->window_));
    return scope.Close(Boolean::New(resizable));
}
Handle<Value> WebKitWindow::GetFocused(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    bool resizable = gtk_window_get_resizable(GTK_WINDOW(window->window_));
    return scope.Close(Boolean::New(resizable));
}

/* SIGNAL HANDLING */
void WebKitWindow::Destroy(GtkWidget* widget, WebKitWindow* window)
{
    HandleScope scope;
    assert(window);
    assert(window->window_);
    window->Emit("close", 0, NULL);
    quit_loop();
}
void WebKitWindow::ConsoleMessage(GtkWidget* widget, const gchar* message, unsigned int line, const gchar* source, WebKitWindow* window)
{
    HandleScope scope;
    assert(window);
    assert(window->window_);
    Handle<Value> args[3];
    args[0] = NODE_SYMBOL(message);
    args[1] = NODE_CONSTANT(line);
    args[2] = NODE_SYMBOL(source);
    window->Emit("console", 3, args);
}

void WebKitWindow::RefreshTitle(GtkWidget* widget, GParamSpec* pspec, WebKitWindow* window)
{
    HandleScope scope;
    assert(window);
    assert(window->window_);
    assert(window->view_);
    const gchar *title = webkit_web_view_get_title(WEBKIT_WEB_VIEW(window->view_));
    if (title){
        gtk_window_set_title(GTK_WINDOW(window->window_), title);
    }
}

/* MISC */
bool WebKitWindow::Emit(const char* event, int argCount, Handle<Value> emitArgs[]) {
    //return true; //Temporarily disabled
    HandleScope scope;

    //Format arguments to pass to v8::Function
    int nArgCount = argCount + 1;
    Handle<Value> *nEmitArgs = new Handle<Value>[nArgCount];

    //Integrity checks
    if (nEmitArgs == NULL) {
        return false;
    }

    if (this->handle_.IsEmpty()){
        return false;
    }

    //nEmitArgs = ['coolEvent', other args...]
    nEmitArgs[0] = String::New(event);
    if(emitArgs != NULL){
        for (int i=0; i < argCount; i++) {
            nEmitArgs[i + 1] = emitArgs[i];
        }
    }

    //Emit event
    Local<Value> emit_v = this->handle_->Get(emit_symbol);
    if (!emit_v->IsFunction()) {
        return false;
    }
    Local<Function> emit = Local<Function>::Cast(emit_v);

    TryCatch try_catch;
    emit->Call(this->handle_, nArgCount, nEmitArgs);

    //Cleanup
    delete [] nEmitArgs;

    if (try_catch.HasCaught()) {
        FatalException(try_catch);
    }
    return true;
}

/* EVENT LOOP */
//This is all from EV::Glib by Marc Lehmann.
struct econtext {
  GPollFD *pfd;
  ev_io *iow;
  int nfd, afd;
  gint maxpri;

  ev_prepare pw;
  ev_check cw;
  ev_timer tw;

  GMainContext *gc;
};

static void timer_cb (EV_P_ ev_timer *w, int revents) {
  /* nop */
}

static void io_cb (EV_P_ ev_io *w, int revents) {
  /* nop */
}

static void prepare_cb (EV_P_ ev_prepare *w, int revents) {
  struct econtext *ctx = (struct econtext *)(((char *)w) - offsetof (struct econtext, pw));
  gint timeout;
  int i;

  g_main_context_dispatch (ctx->gc);

  g_main_context_prepare (ctx->gc, &ctx->maxpri);

  while (ctx->afd < (ctx->nfd = g_main_context_query  (
                                                       ctx->gc,
                                                       ctx->maxpri,
                                                       &timeout,
                                                       ctx->pfd,
                                                       ctx->afd))) {
    free (ctx->pfd);
    free (ctx->iow);

    ctx->afd = 1;
    while (ctx->afd < ctx->nfd)
      ctx->afd <<= 1;

    ctx->pfd = (GPollFD*) malloc (ctx->afd * sizeof (GPollFD));
    ctx->iow = (ev_io*) malloc (ctx->afd * sizeof (ev_io));
  }

  for (i = 0; i < ctx->nfd; ++i) {
    GPollFD *pfd = ctx->pfd + i;
    ev_io *iow = ctx->iow + i;

    pfd->revents = 0;

    ev_io_init (
                iow,
                io_cb,
                pfd->fd,
                (pfd->events & G_IO_IN ? EV_READ : 0)
                | (pfd->events & G_IO_OUT ? EV_WRITE : 0)
                );
    iow->data = (void *)pfd;
    ev_set_priority (iow, EV_MINPRI);
    ev_io_start (EV_A_ iow);
  }

  if (timeout >= 0) {
    ev_timer_set (&ctx->tw, timeout * 1e-3, 0.);
    ev_timer_start (EV_A_ &ctx->tw);
  }
}

static void check_cb (EV_P_ ev_check *w, int revents) {

  struct econtext *ctx = (struct econtext *)(((char *)w) - offsetof (struct econtext, cw));
  int i;

  for (i = 0; i < ctx->nfd; ++i) {
    ev_io *iow = ctx->iow + i;

    if (ev_is_pending (iow))	{
      GPollFD *pfd = ctx->pfd + i;
      int revents = ev_clear_pending (EV_A_ iow);

      pfd->revents |= pfd->events &
        ((revents & EV_READ ? G_IO_IN : 0)
         | (revents & EV_WRITE ? G_IO_OUT : 0));
    }

    ev_io_stop (EV_A_ iow);
  }

  if (ev_is_active (&ctx->tw))
    ev_timer_stop (EV_A_ &ctx->tw);

  if (ctx->nfd || GLIB_CHECK_VERSION (2, 30, 0))
    g_main_context_check (ctx->gc, ctx->maxpri, ctx->pfd, ctx->nfd);
}

static struct econtext default_context;

void WebKitWindow::run_loop ()
{
    HandleScope scope;
    ev_ref(EV_DEFAULT_UC);
}

gboolean WebKitWindow::quit_loop ()
{
    ev_unref(EV_DEFAULT_UC);
    //gtk_main_quit();
    return false;
}

extern "C" {
    static void init (Handle<Object> target)
    {
        HandleScope scope;
        WebKitWindow::Initialize(target);
        if (!g_thread_supported()){
            g_thread_init(NULL);
        }
        GMainContext *gc     = g_main_context_default();
        struct econtext *ctx = &default_context;

        g_main_context_acquire (gc);
        ctx->gc  = g_main_context_ref(gc);
        ctx->nfd = 0;
        ctx->afd = 0;
        ctx->iow = 0;
        ctx->pfd = 0;

        ev_prepare_init (&ctx->pw, prepare_cb);
        ev_set_priority (&ctx->pw, EV_MINPRI);
        ev_prepare_start (EV_DEFAULT_UC_ &ctx->pw);
        ev_unref(EV_DEFAULT_UC);

        ev_check_init (&ctx->cw, check_cb);
        ev_set_priority (&ctx->cw, EV_MAXPRI);
        ev_check_start (EV_DEFAULT_UC_ &ctx->cw);
        ev_unref(EV_DEFAULT_UC);

        ev_init (&ctx->tw, timer_cb);
        ev_set_priority (&ctx->tw, EV_MINPRI);
    }

    NODE_MODULE(WebKitWindow, init);
}
