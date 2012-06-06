#include "WebKitWindow.h"
#include "HookedPage.h"

using namespace v8;
using namespace node;

Persistent<FunctionTemplate> WebKitWindow::s_ct;

WebKitWindow::WebKitWindow() {
    //Create UI components
    int argc = 1;
    char **argv = NULL;

    app_ = new QApplication(argc, argv);
    app_->setOrganizationName("Fractal");
    app_->setApplicationName("Pane");
    window_ = new QMainWindow(0);
    view_ = new QWebView(window_);
    page_ = new HookedPage(this, view_);
    view_->setPage(page_);
    window_->setCentralWidget(view_);

    view_->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    view_->settings()->setOfflineStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    view_->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    view_->settings()->setOfflineWebApplicationCachePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    view_->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    view_->settings()->setLocalStoragePath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    view_->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    view_->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
}

WebKitWindow::~WebKitWindow() {
    delete app_;
}

void WebKitWindow::Initialize(Handle<Object> target)
{
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(NODE_SYMBOL("WebKitWindow"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "processEvents", ProcessEvents);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "close", Close);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "show", Show);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "reload", Reload);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "move", Move);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "screenshot", Screenshot);

    NODE_SET_PROTOTYPE_METHOD(s_ct, "setMaximized", SetMaximized);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "setMinimized", SetMinimized);
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

Handle<Value> WebKitWindow::New (const Arguments &args)
{
    HandleScope scope;
    if (!args.IsConstructCall())
    {
        return ThrowException(Exception::TypeError(NODE_SYMBOL("Use the new operator to create instances of this object.")));
    }

    WebKitWindow *window = new WebKitWindow();
    window->Wrap(args.This());
    return scope.Close(args.This());
}

/* FUNCTIONS */
Handle<Value> WebKitWindow::ProcessEvents(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->app_);
    if(window->app_->hasPendingEvents()){
        window->app_->processEvents();
    }
    return scope.Close(args.This());
}

Handle<Value> WebKitWindow::Show(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    #if defined Q_OS_SYMBIAN || defined Q_WS_HILDON || defined Q_WS_MAEMO_5 || defined Q_WS_SIMULATOR
         window->window_->showMaximized();
    #else
         window->window_->show();
    #endif
    window->Emit("show", 0, NULL);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Close(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    window->window_->close();
    window->app_->exit(0);
    window->Emit("close", 0, NULL);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Reload(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    window->view_->reload();
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
    window->window_->move(x, y);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Screenshot(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    ARG_CHECK_STRING(0, title);
    String::Utf8Value title(args[0]->ToString());
    window->page_->screenshot(QString(*title));
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
    if (maximized)
    {
        window->window_->showMaximized();
    }
    else
    {
        window->window_->showNormal();
    }
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::SetMinimized(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_BOOL(0, minimized);
    bool minimized = args[0]->BooleanValue();
    if (minimized)
    {
        window->window_->showMinimized();
    }
    else
    {
        window->window_->showNormal();
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

    if (fullscreen)
    {
        window->window_->showFullScreen();
    }
    else
    {
        window->window_->showNormal();
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
    window->window_->setWindowTitle(QString(*title));
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetTitle(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    const char *title = CString(window->view_->windowTitle());
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
    window->view_->setUrl(QUrl(*url));
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetUrl(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->view_);
    const char *uri = CString(window->view_->url().toString());
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
    window->view_->setHtml(QString(*html), QUrl("file:///"));
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
    QString out = window->view_->page()->mainFrame()->evaluateJavaScript(*script).toString();
    return scope.Close(NODE_SYMBOL(out.toAscii()));
}
Handle<Value> WebKitWindow::SetSize(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    ARG_CHECK_UINT32(0, height);
    ARG_CHECK_UINT32(1, width);
    int height = args[0]->ToInteger()->Value();
    int width = args[1]->ToInteger()->Value();
    window->window_->resize(width, height);
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetSize(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    int height = window->window_->height();
    int width = window->window_->width();
    Handle<Array> array = Array::New(2);
    if (array.IsEmpty())
    {
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
    //TODO
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::GetResizable(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    bool resizable = false;
    //TODO
    return scope.Close(Boolean::New(resizable));
}
Handle<Value> WebKitWindow::GetFocused(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    bool focused = window->window_->hasFocus();
    return scope.Close(Boolean::New(focused));
}

/* Events */
void WebKitWindow::PageLoaded(bool success)
{
    HandleScope scope;
    Handle<Value> args[1];
    args[0] = Boolean::New(success);
    Emit("loaded", 1, args);
}
void WebKitWindow::ConsoleMessage(const QString &message, int line, const QString &source)
{
    HandleScope scope;
    Handle<Value> args[3];
    args[0] = NODE_SYMBOL(message.toAscii());
    args[1] = NODE_CONSTANT(line);
    args[2] = NODE_SYMBOL(source.toAscii());
    Emit("console", 3, args);
}

/* MISC */
bool WebKitWindow::Emit(const char *event, int argCount, Handle<Value> emitArgs[])
{
    HandleScope scope;

    //Format arguments to pass to v8::Function
    int nArgCount = argCount + 1;
    Handle<Value> *nEmitArgs = new Handle<Value>[nArgCount];

    //Integrity checks
    if (nEmitArgs == NULL)
    {
        return false;
    }

    if (this->handle_.IsEmpty())
    {
        return false;
    }

    //nEmitArgs = ['coolEvent', other args...]
    nEmitArgs[0] = String::New(event);
    if (emitArgs != NULL)
    {
        for (int i = 0; i < argCount; i++)
        {
            nEmitArgs[i + 1] = emitArgs[i];
        }
    }

    //Emit event
    Local<Value> emit_v = this->handle_->Get(NODE_SYMBOL("emit"));
    if (!emit_v->IsFunction())
    {
        return false;
    }
    Local<Function> emitf = Local<Function>::Cast(emit_v);

    TryCatch try_catch;
    emitf->Call(this->handle_, nArgCount, nEmitArgs);

    //Cleanup
    delete [] nEmitArgs;

    if (try_catch.HasCaught())
    {
        FatalException(try_catch);
    }
    return true;
}

extern "C" {
    static void init (Handle<Object> target)
    {
        HandleScope scope;
        WebKitWindow::Initialize(target);
    }
    NODE_MODULE(WebKitWindow, init);
}
