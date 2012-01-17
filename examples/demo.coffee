Pane = require '../lib/Pane'
  
doStuff = (window) ->
  console.log window.getFocused()
  console.log window.getTitle()
  console.log window.getUrl()
  console.log window.getSize()
  console.log window.getResizable()

  window.on 'open', -> console.log 'open'
  window.on 'close', -> console.log 'close'
  window.on 'console', (msg, line, src) -> 
    console.log "'#{msg}' line #{line} - #{src}"

  window.execute 'console.log("test2");'
  window.execute 'document.writeln("world");'
  
  window.open()
  
  moveit = -> 
    window.move 500, 100
    window.execute 'document.writeln(" - i moved!");'
    window.setTitle 'new title heyooo'
    
  setTimeout moveit, 5000
  
  #window.reload()
  #window.close()
  
test = new Pane 
  javascript: 'document.writeln("hello");' # Alias for execute
  title: 'Hello NodeAZ!' # Alias for setTitle
  height: 500 # Alias for setSize
  width: 500 # Alias for setSize
  resizable: true # Alias for setResizable
  ready: doStuff
