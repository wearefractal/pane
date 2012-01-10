**pane is a cross-platform GTK+ WebKit binding for node**


## Installation
    
To install pane, use [npm](http://github.com/isaacs/npm):

    $ sudo apt-get install -y libgtk2.0-dev libglib2.0-dev libwebkitgtk-dev
    $ npm install pane

## Usage

```coffee-script
Pane = require 'pane'
window = new Pane 
  url: 'http://yoursite.com'
  height: 300 # Default 250
  width: 300 # Default 250
  resizable: true # Default true
  scrollable: false # Default false
  
window.open()
window.close()
```

## Examples

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
