{EventEmitter} = require 'events'
WebKitWindow = require('../build/Release/WebKitWindow').WebKitWindow

WebKitWindow::[key] = val for key, val of EventEmitter::
WebKitWindow::initialize = ->
  fn = =>
    @processEvents()
    process.nextTick fn
  fn()

WebKitWindow::open = (cb) ->
  @once 'loaded', cb if cb?
  @show()

WebKitWindow::resize = WebKitWindow::setSize
WebKitWindow::maximize = (b=true) -> @setMaximized b
WebKitWindow::minimize = (b=true) -> @setMinimized b
WebKitWindow::fullscreen = (b=true) -> @setFullscreen b
WebKitWindow::resizable = (args...) -> (if args.length > 0 then @setResizable args... else @getResizable())
WebKitWindow::title = (args...) -> (if args.length > 0 then @setTitle args... else @getTitle())
WebKitWindow::url = (args...) -> (if args.length > 0 then @setUrl args... else @getUrl())
WebKitWindow::html = (args...) -> (if args.length > 0 then @setHtml args... else @getHtml())

module.exports = WebKitWindow