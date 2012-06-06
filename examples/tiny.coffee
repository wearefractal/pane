Pane = require '../lib/Pane'
log = require 'node-log'
log.setName 'pane-demo'

opt = 
  title: 'Test'
  height: 500
  width: 800
  url: 'http://cnn.com'

window = new Pane opt

window.on 'console', (msg, line, src) -> console.log msg, line, src
window.execute 'console.log("hay");'
console.log window.execute '1+1'

window.open ->
  console.log 'page loaded'
  window.screenshot __dirname + '/test.png'