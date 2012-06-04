{EventEmitter} = require 'events'
WebKitWindow = require('../build/Release/WebKitWindow').WebKitWindow

WebKitWindow::[key] = val for key, val of EventEmitter::
WebKitWindow::initialize = ->
  fn = =>
    @processEvents()
    process.nextTick fn
  fn()

WebKitWindow::resize = WebKitWindow::setSize
WebKitWindow::maximize = (b=true) -> @setMaximized b
WebKitWindow::minimize = (b=true) -> @setMinimized b
WebKitWindow::fullscreen = (b=true) -> @setFullscreen b
WebKitWindow::resizable = (b) -> (if b then @setResizable b else @getResizable())
WebKitWindow::title = (str) -> (if str then @setTitle str else @getTitle())
WebKitWindow::url = (str) -> (if str then @setUrl str else @getUrl())
WebKitWindow::html = (str) -> (if str then @setHtml str else @getHtml())

module.exports = WebKitWindow