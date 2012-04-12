{EventEmitter} = require 'events'
WebKitWindow = require './WebKitWindow'

class Pane extends EventEmitter
  constructor: ({js, html, url, height, width, resizable, title, fullscreen, maximized}, cb) ->
    process.nextTick ->
      @window = new WebKitWindow
      
      # First
      @window.setSize height, width if height? and width?
      @window.setMaximized maximized if maximized?
      @window.setFullscreen fullscreen if fullscreen?
      @window.setResizable resizable if resizable?
      @window.setTitle title if title?
      
      @window.setUrl url if url?
      @window.setHtml html if html?
      @window.execute js if js?
      cb @window if cb?
      @window.initialize()
  
module.exports = Pane
