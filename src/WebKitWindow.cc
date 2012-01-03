#include <cstring> // strlen()
#include <node.h>
#include <node_events.h>
#include <assert.h>
#include <v8.h>
#include <QMainWindow>
#include <QtGui>
#include <QtWebKit>
#include <QWebView>

using namespace v8;
using namespace node;
static Persistent<String> open_symbol;
static Persistent<String> close_symbol;

#define HEIGHT_SYMBOL String::NewSymbol("height")
#define WIDTH_SYMBOL String::NewSymbol("width")
#define TITLE_SYMBOL String::NewSymbol("title")

#ifdef DEBUGMODE
#define DEBUG(msg) \
	g_print(msg)
#define DEBUG_VALUE(msg, value) \
	g_print(msg, value)
#else
#define DEBUG(msg)
#define DEBUG_VALUE(msg, value)
#endif

class WebKitWindow : public EventEmitter {
 public:
  static void Initialize (v8::Handle<v8::Object> target)
  {
    window_ = new QtGui
    view_ = new QWebView(window_);
    view_->load(QUrl("http://qt.nokia.com/"));
    view_->show();
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    t->Inherit(EventEmitter::constructor_template);
    t->InstanceTemplate()->SetInternalFieldCount(1);
    
    open_symbol = NODE_PSYMBOL("open");
    close_symbol = NODE_PSYMBOL("close");
    
    NODE_SET_PROTOTYPE_METHOD(t, "setTitle", SetTitle);
    NODE_SET_PROTOTYPE_METHOD(t, "setHeight", SetHeight);
    NODE_SET_PROTOTYPE_METHOD(t, "setWidth", SetWidth);
    NODE_SET_PROTOTYPE_METHOD(t, "load", Load);
    NODE_SET_PROTOTYPE_METHOD(t, "close", Close);
    
    //t->PrototypeTemplate()->SetAccessor(HEIGHT_SYMBOL, WindowHeightGetter);
    //t->PrototypeTemplate()->SetAccessor(WIDTH_SYMBOL, WindowWidthGetter);
    t->PrototypeTemplate()->SetAccessor(TITLE_SYMBOL, WindowTitleGetter);
    
    target->Set(String::NewSymbol("WebKitWindow"), t->GetFunction());
  }

  void Close (Local<Value> exception = Local<Value>())
  {
    HandleScope scope;
    if (exception.IsEmpty()) {
      Emit(close_symbol, 0, NULL);
    } else {
      Emit(close_symbol, 1, &exception);
    }
    Unref();
  }
 
  
 protected:
  static Handle<Value> New (const Arguments& args)
  {
    HandleScope scope;
    WebKitWindow *window = new WebKitWindow();
    window->Wrap(args.This());
    return args.This();
  }
  
  static Handle<Value> WindowHeightGetter (Local<String> property, const AccessorInfo& info)
  {
    WebKitWindow *window = ObjectWrap::Unwrap<WebKitWindow>(info.This());
    assert(window);
    assert(property == WINDOW_HEIGHT_SYMBOL);
    HandleScope scope;
    return scope.Close(String::NewSymbol(window.title()));
  }

  WebKitWindow () : EventEmitter () 
  {
  }

  ~WebKitWindow ()
  {
  }
  
  QWebView *window_;
  QWebView *view_;
};

extern "C"
void init (Handle<Object> target) 
{
  HandleScope scope;
  WebKitWindow::Initialize(target);
}
