Pane = require '../'
should = require 'should'
require 'mocha'

describe 'pane', ->
  describe 'construct', ->
    it 'should work with no options', (done) ->
      win = new Pane
      should.exist win
      done()

describe 'window', ->
  describe 'open()', ->
    it 'should open', (done) ->
      win = new Pane
      win.on 'open', done
      win.open()

    it 'should open with callback for domReady', (done) ->
      win = new Pane url: 'http://www.google.com/'
      win.open (ok) ->
        ok.should.equal true
        done()

  describe 'url()', ->
    it 'should set the url', (done) ->
      win = new Pane
      win.url 'http://www.google.com/'
      win.url().should.equal 'http://www.google.com/'
      done()

    it 'should get the url', (done) ->
      win = new Pane
      win.url().should.equal ''
      done()

  describe 'title()', ->
    it 'should set the title', (done) ->
      win = new Pane
      win.title 'test'
      win.title().should.equal 'test'
      done()

    it 'should get the title', (done) ->
      win = new Pane
      win.title().should.equal ''
      done()

  describe 'execute()', ->
    it 'should get value', (done) ->
      win = new Pane
      out = win.execute '1+1'
      out.should.equal '2'
      done()
