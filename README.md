**pane is a cross-platform QtWebKit binding for node**

Old GTK version: http://registry.npmjs.org/pane/-/pane-0.0.1.tgz

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

opt =
  title: 'Test'
  height: 500
  width: 500
  html: 'Hello world!'

test = new Pane opt, (window) ->
  window.on 'open', -> console.log 'opened!'
  window.on 'close', -> process.exit()

  window.open()
  window.execute 'console.log("test2");'

  move = ->
    console.log 'move'
    window.move 500, 100
    window.execute 'document.writeln(" - i moved!");'
    window.setTitle 'new title heyooo'

  setTimeout move, 1000

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
