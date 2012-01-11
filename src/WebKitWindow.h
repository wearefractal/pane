#ifndef WEBKITWINDOW_H_
#define WEBKITWINDOW_H_

#include "node_defs.h"
#include "node_async.h"
#include <uv.h>
#include <assert.h>
#include <v8.h>
#include <node.h>
#include <gtk/gtk.h>
#include <webkit/webkitwebview.h>
#include <node_object_wrap.h>

using namespace v8;
using namespace node;

class WebKitWindow : public ObjectWrap {
  public:    
    WebKitWindow() : ObjectWrap() {}
    ~WebKitWindow() {}
    static Persistent<FunctionTemplate> s_ct;
    static Persistent<String> emit_symbol;
    static void Initialize(Handle<Object> target);

    /* FUNCTIONS */
    static Handle<Value> Close(const Arguments &args);
    static Handle<Value> Open(const Arguments &args);

    /* SIGNALS */
    static void RefreshTitle(GtkWidget* widget);
    static void Destroy(GtkWidget* widget, WebKitWindow* window);

    /* ACCESSORS */
    static Handle<Value> WindowTitleGetter(Local<String> property, const AccessorInfo &info);

    /* MISC */
    bool Emit(const char* event, int argc, Handle<Value> argv[]);

  private:
    static Handle<Value> New(const Arguments &args);
    GtkWidget* window_;
    GtkWidget* view_;
};

#endif  // WEBKITWINDOW_H_
