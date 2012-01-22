Pane = require '../lib/Pane'
log = require 'node-log'
log.setName 'pane-demo'

doStuff = (window) ->
  window.open()
  log.debug window.getFocused()
  log.debug window.getTitle()
  log.debug window.getUrl()
  log.debug window.getSize()
  log.debug window.getResizable()
  
  window.on 'open', -> console.log 'open'
  window.on 'close', -> console.log 'close'
  #window.on 'console', (msg, line, src) -> console.log "'#{msg}' line #{line} - #{src}"
  
  
  window.execute 'console.log("test2");'
 
  moveit = -> 
    console.log 'move'
    window.move 500, 100
    window.execute 'document.writeln(" - i moved!");'
    window.setTitle 'new title heyooo'
    
  setTimeout moveit, 1000
  #window.reload()
  #window.close()
  
  
test = new Pane 
  url: 'http://google.com'
  #html: 'hi'
  js: 'console.log("test1");'
  title: 'Test' # Alias for setTitle
  height: 500 # Alias for setSize
  width: 500 # Alias for setSize
  resizable: true # Alias for setResizable
  ready: doStuff

console.log 'Event loop restored'
