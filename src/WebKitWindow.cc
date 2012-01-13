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
    s_ct->SetClassName(String::NewSymbol("WebKitWindow"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "close", Close);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "open", Open);

    s_ct->PrototypeTemplate()->SetAccessor(String::NewSymbol("title"), WindowTitleGetter);

    target->Set(String::NewSymbol("WebKitWindow"), t->GetFunction());
}

Handle<Value> WebKitWindow::New (const Arguments& args)
{
    HandleScope scope;
    if (!args.IsConstructCall()) {
        return ThrowException(Exception::TypeError(String::New("Use the new operator to create instances of this object.")));
    }
    //Check types of arguments
    ARG_CHECK_STRING(0, url);
    ARG_CHECK_UINT32(1, height);
    ARG_CHECK_UINT32(2, width);
    ARG_CHECK_BOOL(3, resizable);
    ARG_CHECK_BOOL(4, scrollable);

    //Cast arguments to native types
    String::Utf8Value url(args[0]->ToString());
    int height = args[1]->Int32Value();
    int width = args[2]->Int32Value();
    bool resizable = args[3]->BooleanValue();
    //TODO: Scrollable webkit_web_view from this
    bool scrollable = args[4]->BooleanValue();

    //Initialize glib threading support and libgtk
    if (!g_thread_supported()){
        g_thread_init(NULL);
    }
    gtk_init(NULL, NULL);

    WebKitWindow *window = new WebKitWindow;
    window->Wrap(args.This());
    //Create UI components
    window->window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    window->view_ = webkit_web_view_new();

    //Connect signals from UI components to JS events
    //g_signal_connect (window->window_, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window->window_), "destroy", G_CALLBACK(window->Destroy), window);
    g_signal_connect(window->view_, "title-changed", G_CALLBACK(window->RefreshTitle), window);

    //Add components to window
    gtk_container_add(GTK_CONTAINER(window->window_), window->view_);

    //Window preferences
    gtk_window_set_default_size(GTK_WINDOW(window->window_), width, height);
    gtk_window_set_resizable(GTK_WINDOW(window->window_), resizable);

    //Load url and show all components
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(window->view_), *url);
    gtk_widget_show_all(window->window_);

    return scope.Close(args.This());
}

/* FUNCTIONS */

Handle<Value> WebKitWindow::Open(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    //gtk_main();

    Baton* baton = new Baton();
    baton->request.data = baton;
    int status = uv_queue_work(uv_default_loop(), &baton->request, GTKWork, GTKAfter);
    assert(status == 0);
    window->Emit("open", 0, NULL);

    return scope.Close(Undefined());
}
Handle<Value> WebKitWindow::Close(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    window->Emit("close", 0, NULL);
    gtk_main_quit();
    return scope.Close(Undefined());
}


/* GETTERS AND SETTERS */
Handle<Value> WebKitWindow::WindowTitleGetter (Local<String> property, const AccessorInfo& info)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(info.This());
    assert(window);
    //assert(property === "title property");
    return scope.Close(String::NewSymbol(gtk_window_get_title(GTK_WINDOW(window->window_))));
}


/* SIGNAL HANDLING */
void WebKitWindow::Destroy (GtkWidget* widget, WebKitWindow* window)
{
    HandleScope scope;
    assert(window);
    window->Emit("close", 0, NULL);
    gtk_main_quit();
}

void WebKitWindow::RefreshTitle (GtkWidget* widget, WebKitWindow* window)
{
    HandleScope scope;
    assert(window);
    //Set title of main window to web_view title
    gtk_window_set_title(GTK_WINDOW(window->window_), webkit_web_view_get_title(WEBKIT_WEB_VIEW(window->view_)));
}

/* MISC */
bool WebKitWindow::Emit(const char* event, int argCount, Handle<Value> emitArgs[]) {
    return true; //Temporarily disabled
    HandleScope scope;

    //Format arguments to pass to v8::Function
    int nArgCount = argCount + 1;
    Handle<Value>* nEmitArgs = new Handle<Value>[nArgCount];

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

/* GTK EVENT LOOP */

void GTKWork(uv_work_t* req) {
    Baton* baton = static_cast<Baton*>(req->data);
    while(true){
        if (gtk_events_pending()){
            gtk_main_iteration();
        }

    }
    printf("GTK loop done\n");
}

void GTKAfter(uv_work_t* req) {
    HandleScope scope;
    Baton* baton = static_cast<Baton*>(req->data);
    printf("Async loop done\n");
    delete baton;
}


extern "C" {
    static void init (Handle<Object> target)
    {
      HandleScope scope;
      WebKitWindow::Initialize(target);
    }

    NODE_MODULE(WebKitWindow, init);
}
