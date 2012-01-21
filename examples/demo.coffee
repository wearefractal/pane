Pane = require '../lib/Pane'
log = require 'node-log'
log.setName 'pane-demo'

doStuff = (window) ->
  console.log 'ready called'
  window.open()
  
  
  window.on 'open', -> console.log 'open'
  window.on 'close', -> console.log 'close'
  window.on 'console', (msg, line, src) -> 
    console.log "'#{msg}' line #{line} - #{src}"
  
  log.debug window.getFocused()
  log.debug window.getTitle()
  log.debug window.getUrl()
  log.debug window.getSize()
  log.debug window.getResizable()
  
  window.execute 'console.log("test2");'
  window.execute 'document.writeln("world");'
 
  moveit = -> 
    window.move 500, 100
    window.execute 'document.writeln(" - i moved!");'
    window.setTitle 'new title heyooo'
    
  setTimeout moveit, 5000
  window.open()
  #window.reload()
  #window.close()
  
test = new Pane 
  url: 'http://trycodex.nodester.com'
  #html: 'hi'
  #js: "console.log('testi');"
  title: 'Codex' # Alias for setTitle
  height: 500 # Alias for setSize
  width: 500 # Alias for setSize
  resizable: true # Alias for setResizable
  ready: doStuff

console.log 'Event loop restored'
