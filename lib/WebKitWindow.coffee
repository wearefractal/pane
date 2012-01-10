{EventEmitter} = require 'events'
WebKitWindow = require('../WebKitWindow').WebKitWindow

WebKitWindow::[key] = val for key, val of EventEmitter::

module.exports = WebKitWindow
