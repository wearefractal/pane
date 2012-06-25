Pane = require '../lib/Pane'
log = require 'node-log'
log.setName 'pane-demo'

opt = 
  title: 'Test'
  height: 500
  width: 800
  html: 'Hello world!'

window = new Pane opt

log.debug window.getFocused()
log.debug window.title()
log.debug window.url()
log.debug window.getSize()
log.debug window.resizable()

window.on 'open', -> console.log 'open'
window.on 'close', -> 
  console.log 'close'
  process.exit()
window.on 'console', (msg, line, src) -> console.log "'#{msg}' line #{line} - #{src}"

window.open()
window.execute 'console.log("test2");'

move = ->
  console.log 'move'
  window.move 500, 100
  window.execute 'document.writeln(" - i moved!");'
  window.title 'new title heyooo'

setTimeout move, 1000