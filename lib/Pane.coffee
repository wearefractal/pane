{EventEmitter} = require 'events'
WebKitWindow = require './WebKitWindow'

class Pane extends EventEmitter
  constructor: (opt) ->
    @window = new WebKitWindow
    @window.initialize()

    if opt?
      {js, html, baseUrl, url, height, width, resizable, title, fullscreen, maximized, minimized} = opt
      @window.resize height, width if height? and width?
      @window.maximize maximized if maximized?
      @window.minimize minimized if minimized?
      @window.fullscreen fullscreen if fullscreen?
      @window.setResizable resizable if resizable?
      @window.title title if title?

      @window.url url if url?
      @window.html html, baseUrl if html? and baseUrl?
      @window.html html if html? and not baseUrl?
      @window.execute js if js?
    return @window

module.exports = Pane
