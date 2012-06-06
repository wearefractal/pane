#include "HookedPage.h"
#include "WebKitWindow.h"

HookedPage::HookedPage(WebKitWindow *window, QObject *parent) : QWebPage(parent) {
  window_ = window;
  connect(this, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
}

void HookedPage::loadStarted() {
}

void HookedPage::loadFinished(bool ok) {
  window_->PageLoaded(ok);
}

void HookedPage::javaScriptConsoleMessage(const QString &message, int line, const QString &sourceID) {
  QFileInfo fi(sourceID);
  window_->ConsoleMessage(message, line, fi.fileName());
}

void HookedPage::screenshot(const QString &filename) {
  QSize oldSize = viewportSize();
  setViewportSize(mainFrame()->contentsSize());
  QImage *image = new QImage(mainFrame()->contentsSize(), QImage::Format_ARGB32);
  QPainter *painter = new QPainter(image);
  mainFrame()->render(painter);
  painter->end();
  image->save(filename);
  setViewportSize(oldSize);
}

#include "HookedPage.moc"