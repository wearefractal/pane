WebKitWindow = require '../WebKitWindow'

class Pane extends WebKitWindow
  constructor: (title, height, width) ->
    @setTitle title if title
    @setHeight height if height
    @setWidth width if width
    
module.exports = Pane
  #TODO: Everything
