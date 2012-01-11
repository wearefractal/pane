sys = require 'util'
Pane = require '../lib/Pane'

window1 = new Pane 
  url: 'http://google.com/'
  height: 500 # Default 250
  width: 800 # Default 250
  resizable: true # Default true
  scrollable: false # Default false
  
window1.on 'open', -> 
  console.log 'window1 opened'
  
window1.on 'close', -> 
  console.log 'window1 closed'
  
window1.open();

console.log("Event loop restored!");
###
window2 = new Pane 'http://github.com', 200, 200, false, false
window2.on 'open', -> 
  console.log 'window2 opened'
  window2.on 'close', -> 
  console.log 'window2 closed'

window2.open();
###
