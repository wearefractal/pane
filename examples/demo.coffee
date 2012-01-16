sys = require 'util'
Pane = require '../lib/Pane'
  
doStuff = (window) ->
  console.log window.getFocused()
  console.log window.getTitle()
  console.log window.getUrl()
  console.log window.getSize()
  console.log window.getResizable()


  window.on 'open', -> console.log 'open'
  window.on 'close', -> console.log 'close'
  window.on 'console', (msg, line) -> console.log "'#{msg}' line #{line}"

  window.open()

  window.execute 'console.log("test2");'
  # window.setMaximized true
  # window.setFullscreen true
  
test = new Pane 
  #url: 'http://google.com/'
  html: 'hi'
  javascript: 'console.log("test");'
  title: 'Cool test'
  height: 500
  width: 800
  resizable: true # Default true
  ready: doStuff
