{EventEmitter} = require 'events'
WebKitWindow = require('../build/Release/WebKitWindow').WebKitWindow

WebKitWindow::[key] = val for key, val of EventEmitter::
WebKitWindow::initialize = ->
  fn = => 
    @processEvents()
    process.nextTick fn
  process.nextTick fn
WebKitWindow::resize = WebKitWindow::setSize

module.exports = WebKitWindow