{EventEmitter} = require 'events'
WebKitWindow = require './WebKitWindow'

class Pane extends EventEmitter
  constructor: ({@url, @height, @width, @resizable, @scrollable}) ->
    throw "URL required" unless @url
    @height ?= 250
    @width ?= 250
    @resizable ?= true
    @scrollable ?= false
    @window = new WebKitWindow @url, @height, @width, @resizable, @scrollable
   
  open: -> 
    @window.on 'open', -> @emit 'open'
    @window.on 'close', -> @emit 'close'
    @window?.open()

  close: -> @window?.close()
    
module.exports = Pane
