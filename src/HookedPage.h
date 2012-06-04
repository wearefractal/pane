#ifndef _HOOKEDPAGE_H
#define _HOOKEDPAGE_H

#include <QtWebKit>

class WebKitWindow;

class HookedPage : public QWebPage {
  public:
    HookedPage(WebKitWindow *window, QObject *parent = 0);

  protected:
    void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID);

  private:
    WebKitWindow *window_;
};

#endif //_HOOKEDPAGE_H
