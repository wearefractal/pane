#ifndef WEBKITWINDOW_H_
#define WEBKITWINDOW_H_

#include "node_defs.h"
#include <ev.h>
#include <stdlib.h>
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
    static Handle<Value> Reload(const Arguments &args);
    static Handle<Value> Move(const Arguments &args);
    static Handle<Value> SetMaximized(const Arguments &args);
    static Handle<Value> SetFullscreen(const Arguments &args);
    static Handle<Value> SetUrl(const Arguments &args);
    static Handle<Value> GetUrl(const Arguments &args);
    static Handle<Value> SetHtml(const Arguments &args);
    static Handle<Value> ExecuteScript(const Arguments &args);
    static Handle<Value> SetSize(const Arguments &args);
    static Handle<Value> GetSize(const Arguments &args);
    static Handle<Value> SetResizable(const Arguments &args);
    static Handle<Value> GetResizable(const Arguments &args);
    static Handle<Value> SetTitle(const Arguments &args);
    static Handle<Value> GetTitle(const Arguments &args);
    static Handle<Value> GetFocused(const Arguments &args);

    /* SIGNALS */
    static void ConsoleMessage(GtkWidget* widget, const gchar* message, unsigned int line, const gchar* sourceId, WebKitWindow* window);
    static void RefreshTitle(GtkWidget* widget, GParamSpec* pspec, WebKitWindow* window);
    static void Destroy(GtkWidget* widget, WebKitWindow* window);

    /* MISC */
    bool Emit(const char* event, int argc, Handle<Value> argv[]);

  private:
    static Handle<Value> New(const Arguments &args);
    static void run_loop();
    static gboolean quit_loop();
    GtkWidget* window_;
    GtkWidget* view_;
};

#endif  // WEBKITWINDOW_H_
