sys = require 'util'
Pane = require './lib/Pane'

window1 = new Pane 'http://google.com', 200, 200, true, false
console.log window1
window1.on 'open', -> 
  console.log 'window1 opened'
  window1.on 'close', -> 
    console.log 'window1 closed'
  
window1.open();

###
window2 = new Pane 'http://github.com', 200, 200, false, false
window2.on 'open', -> 
  console.log 'window2 opened'
  window2.on 'close', -> 
  console.log 'window2 closed'

window2.open();
###
