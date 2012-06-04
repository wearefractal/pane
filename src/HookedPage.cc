#include "HookedPage.h"
#include "WebKitWindow.h"

HookedPage::HookedPage(WebKitWindow *window, QObject *parent) : QWebPage(parent) {
  window_ = window;
}

void HookedPage::javaScriptConsoleMessage(const QString &message, int line, const QString &sourceID) {
  QFileInfo fi(sourceID);
  window_->ConsoleMessage(message, line, fi.fileName());
}