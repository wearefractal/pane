{
  'targets': [
    {
      'target_name': 'WebKitWindow',
      'sources': [
        'src/WebKitWindow.cc'
      ],
      'conditions': [
        ['OS=="mac"', {
          'include_dirs': [
            'deps/qt-4.8.0/darwin/x64/include',
            'deps/qt-4.8.0/darwin/x64/include/QtCore',
            'deps/qt-4.8.0/darwin/x64/include/QtGui',
            'deps/qt-4.8.0/darwin/x64/include/QtTest'
          ],
          'libraries': [
            # TODO: fix node-gyp behavior that requires ../
            '../deps/qt-4.8.0/darwin/x64/lib/QtCore.framework/QtCore', 
            '../deps/qt-4.8.0/darwin/x64/lib/QtGui.framework/QtGui', 
            '../deps/qt-4.8.0/darwin/x64/lib/QtTest.framework/QtTest'
          ],
        }],
        ['OS=="linux"', {
          'cflags': [
            '<!@(pkg-config --cflags QtCore QtGui QtTest QtWebKit)'
          ],
          'ldflags': [
            '<!@(pkg-config --libs-only-L --libs-only-other QtCore QtGui QtTest QtWebKit)'
          ],
          'libraries': [
            '<!@(pkg-config --libs-only-l QtCore QtGui QtTest QtWebKit)'
          ]
        }],
        ['OS=="win"', {
          'include_dirs': [
              'deps/qt-4.8.0/win32/ia32/include',
              'deps/qt-4.8.0/win32/ia32/include/QtCore',
              'deps/qt-4.8.0/win32/ia32/include/QtGui',
              'deps/qt-4.8.0/win32/ia32/include/QtTest',
              'deps/qt-4.8.0/win32/ia32/include/QtWebKit'
          ],
          'libraries': [
              # TODO: fix node-gyp behavior that requires ../
              '../deps/qt-4.8.0/win32/ia32/lib/QtCore4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtGui4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtTest4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtWebKit4.lib'
          ]
        }]        
      ]
    }
  ]
}