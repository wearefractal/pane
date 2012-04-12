Pane = require '../lib/Pane'
log = require 'node-log'
log.setName 'pane-demo'

opt = 
  title: 'Test'
  height: 500
  width: 500
  html: 'Hello world!'

test = new Pane opt, (window) ->
  log.debug window.getFocused()
  log.debug window.getTitle()
  log.debug window.getUrl()
  log.debug window.getSize()
  log.debug window.getResizable()

  window.on 'open', -> console.log 'open'
  window.on 'close', -> process.exit()
  #window.on 'console', (msg, line, src) -> console.log "'#{msg}' line #{line} - #{src}"

  window.open()
  window.execute 'console.log("test2");'

  move = ->
    console.log 'move'
    window.move 500, 100
    window.execute 'document.writeln(" - i moved!");'
    window.setTitle 'new title heyooo'

  setTimeout move, 1000

console.log 'Event loop restored'
