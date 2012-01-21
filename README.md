**pane is a cross-platform QtWebKit binding for node**


## Installation
    
To install pane, use [npm](http://github.com/isaacs/npm):

    $ npm install pane

## Dependencies

A full installer for each OS will be available soon.

### Ubuntu/Debian

    $ sudo apt-get install -y libqtwebkit-dev

### Fedora/Red Hat - Untested

    Nothing here yet
    
### Windows - Untested

    Nothing here yet

### Mac OSX - Untested
    Nothing here yet
    
## Usage

```coffee-script
Pane = require 'pane'
  
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
  title: 'Cool test' # Alias for setTitle
  height: 250 # Alias for setSize
  width: 250 # Alias for setSize
  resizable: true # Alias for setResizable
  plugins: false # Alias for enablePlugins/disablePlugins
  webgl: true # Alias for enableWebGL/disableWebGL
  fullscreen: false # Alias for setFullScreen
  maximized: false # Alias for setMaximized
  ready: doStuff
  
```

## Examples

![wat](http://i.imgur.com/QSQNu.png)

You can view further examples in the [example folder.](https://github.com/wearefractal/pane/tree/master/examples)

## LICENSE

(MIT License)

Copyright (c) 2011 Fractal <contact@wearefractal.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
