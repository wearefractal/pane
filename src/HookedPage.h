#ifndef _HOOKEDPAGE_H
#define _HOOKEDPAGE_H

#include <QtWebKit>

class WebKitWindow;

class HookedPage : public QWebPage {
  Q_OBJECT

  public:
    HookedPage(WebKitWindow *window, QObject *parent = 0);
    void screenshot(const QString &filename);

  public slots:
    void loadStarted();
    void loadFinished(bool);

  protected:
    void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID);

  private:
    WebKitWindow *window_;
};

#endif //_HOOKEDPAGE_H
