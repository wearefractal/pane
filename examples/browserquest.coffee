Pane = require '../lib/Pane'

opt =
  title: 'BrowserQuest'
  url: 'http://browserquest.mozilla.org/'
  #fullscreen: true

window = new Pane opt
window.open()
window.maximize()