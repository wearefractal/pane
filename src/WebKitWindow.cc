#include "WebKitWindow.h"
#include <stdio.h>

using namespace v8;
using namespace node;

Persistent<FunctionTemplate> WebKitWindow::s_ct;

void WebKitWindow::Initialize(Handle<Object> target)
{
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(NODE_SYMBOL("WebKitWindow"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "start", RunQT);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "close", Close);
    NODE_SET_PROTOTYPE_METHOD(s_ct, "open", Open);

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

Handle<Value> WebKitWindow::New (const Arguments &args)
{
    HandleScope scope;
    if (!args.IsConstructCall())
    {
        return ThrowException(Exception::TypeError(NODE_SYMBOL("Use the new operator to create instances of this object.")));
    }

    WebKitWindow *window = new WebKitWindow();

    //Create UI components
    //QApplication requires argc, argv. v8 doesn't provide these, mock them.
    int argc = 1;
    char **argv = NULL;

    window->app_ = new QApplication(argc, argv);
    window->app_->setOrganizationName("Fractal");
    window->app_->setApplicationName("Pane");
    window->window_ = new QMainWindow(0);
    window->view_ = new QWebView(window->window_);

    //Signals
    //connect(window->view_, SIGNAL(titleChanged(QString)), SLOT(RefreshTitle()));

    //Add stuff
    window->window_->setCentralWidget(window->view_);
    window->Wrap(args.This());
    return scope.Close(args.This());
}

/* FUNCTIONS */
//TODO: FIX THIS
Handle<Value> WebKitWindow::RunQT(const Arguments &args)
{
    //TEST
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->app_);
    window->app_->exec();
    return scope.Close(args.This());
}

Handle<Value> WebKitWindow::Open(const Arguments &args)
{
    //TEST
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->window_);
    #if defined Q_OS_SYMBIAN || defined Q_WS_HILDON || defined Q_WS_MAEMO_5 || defined Q_WS_SIMULATOR
         window->window_->showMaximized();
    #else
         window->window_->show();
    #endif
    window->Emit("open", 0, NULL);
    //window->app_->exec();
    return scope.Close(args.This());
}
Handle<Value> WebKitWindow::Close(const Arguments &args)
{
    HandleScope scope;
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(args.This());
    assert(window);
    assert(window->app_);
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
    window->view_->page()->mainFrame()->evaluateJavaScript(*script);
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
    int height = args[0]->ToInteger()->Value();
    int width = args[1]->ToInteger()->Value();
    window->window_->resize(height, width);
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

/* SIGNAL HANDLING */
/*
void WebKitWindow::ConsoleMessage(WebKitWindow *window)
{
    //TODO
    HandleScope scope;
    assert(window);
    assert(window->window_);
    Handle<Value> args[3];
    args[0] = NODE_SYMBOL(message);
    args[1] = NODE_CONSTANT(line);
    args[2] = NODE_SYMBOL(source);
    window->Emit("console", 3, args);
}
*/
void WebKitWindow::RefreshTitle(WebKitWindow *window)
{
    //TODO IMPLEMENT
    HandleScope scope;
    assert(window);
    assert(window->window_);
    assert(window->view_);
    window->window_->setWindowTitle(window->view_->title());
}

/* MISC */
bool WebKitWindow::Emit(const char *event, int argCount, Handle<Value> emitArgs[])
{
    //return true; //Temporarily disabled
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
