{EventEmitter} = require 'events'
WebKitWindow = require './WebKitWindow'

class Pane extends EventEmitter
  constructor: ({javascript, html, url, height, width, resizable, title, fullscreen, maximized, plugins, webgl, ready}) ->
    process.nextTick ->
      @window = new WebKitWindow
      
      # First
      @window.disablePlugins() if plugins is false
      @window.enableWebGL() if webgl is true
      
      @window.setSize height, width if height? and width?
      @window.setMaximized maximized if maximized?
      @window.setFullscreen fullscreen if fullscreen?
      @window.setResizable resizable if resizable?
      @window.setTitle title if title?
      
      @window.setUrl url if url?
      @window.setHtml html if html?
      @window.execute javascript if javascript?
      
      ready @window if ready?
  
module.exports = Pane
