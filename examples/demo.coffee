Pane = require '../lib/Pane'
  
doStuff = (window) ->
  console.log window.getFocused()
  console.log window.getTitle()
  console.log window.getUrl()
  console.log window.getSize()
  console.log window.getResizable()

  window.on 'open', -> console.log 'open'
  window.on 'close', -> console.log 'close'
  window.on 'console', (msg, line, src) -> console.log "'#{msg}' line #{line} - #{src}"

  window.execute 'console.log("test2");'
  
  window.open()
  window.move 500, 100
  window.reload()
  
  window.close()
  
test = new Pane 
  url: 'http://google.com/' # Alias for setUrl
  html: '<p>pane test</p>' # Alias for setHtml
  javascript: 'document.writeln("hello");' # Alias for execute
  title: 'Cool test' # Alias for setTitle
  height: 250 # Alias for setSize
  width: 250 # Alias for setSize
  resizable: true # Alias for setResizable
  plugins: false # Alias for enablePlugins/disablePlugins
  webgl: true # Alias for enableWebGL/disableWebGL
  fullscreen: false # Alias for setFullScreen
  maximized: false # Alias for setMaximized
  ready: doStuff
