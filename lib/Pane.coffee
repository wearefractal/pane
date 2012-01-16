{EventEmitter} = require 'events'
WebKitWindow = require './WebKitWindow'

class Pane extends EventEmitter
  constructor: ({javascript, html, url, height, width, resizable, title, ready}) ->
    process.nextTick ->
      @window = new WebKitWindow
      
      @window.setTitle title if title?
      @window.setUrl url if url?
      @window.setHtml html if html?
      @window.execute javascript if javascript?
      @window.setSize height, width if height? and width?
      @window.setResizable resizable if resizable?
      ready @window if ready?
  
module.exports = Pane
