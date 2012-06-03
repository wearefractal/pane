Pane = require '../lib/Pane'
log = require 'node-log'
log.setName 'pane-demo'

opt = 
  title: 'Test'
  height: 500
  width: 800
  url: 'http://google.com'

window = new Pane opt

#window.on 'close', process.exit

window.open()
setTimeout (->window.close()), 2000