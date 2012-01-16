**pane is a cross-platform GTK+ WebKit binding for node**


## Installation
    
To install pane, use [npm](http://github.com/isaacs/npm):

    $ npm install pane

## Dependencies

A full installer for each OS will be available soon.

### Ubuntu/Debian - Untested

    $ sudo apt-get install -y libgtk2.0-dev libglib2.0-dev libwebkitgtk-dev libev-dev

### Fedora/Red Hat - Untested

    $ sudo yum install -y gtk+-devel gtk2-devel glib2-devel libwebkitgtk-devel libev-devel
    
### Windows - Untested

Download and install [this.](http://downloads.sourceforge.net/project/gimp-win/Obsolete/GTK%2B/GTK%2B%202.10.13/gtk%2B-2.10.13-setup.exe?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fgimp-win%2Ffiles%2FObsolete%2FGTK%252B%2FGTK%252B%25202.10.13%2F&ts=1326269861&use_mirror=superb-dca2)

### Mac OSX - Untested
    curl -O http://downloads.sourceforge.net/project/gtk-osx/GTK-OSX%20Build/ige-mac-integration-0.9.8.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fgtk-osx%2Ffiles%2F&ts=1326270289&use_mirror=iweb
    tar xzvf ige-mac-integration-0.9.8.tar.bz2
    cd ige-mac-integration-0.9.8
    ./configure
    make
    make install
    
## Usage

```coffee-script
Pane = require 'pane'
window = new Pane 
  url: 'http://nodester.com/nopage'
  height: 500 # Default 250
  width: 800 # Default 250
  resizable: true # Default true
  scrollable: false # Default false
  
window.open()
window.close()
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
