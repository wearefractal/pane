{
  'variables': {
    'module_name': 'WebKitWindow',
	'NODE_ROOT': '',
	'library': 'shared_library',
	'target_arch': 'ia32', 
  },
  'targets': [
    {
      'sources': [
        './src/HelloWorld.cpp',
      ],

	  'target_name': '<(module_name)',
      'type': '<(library)',
	  'product_name':'<(module_name)',
	  'product_extension':'node',
	  'product_dir':'build',
      'product_prefix':'',
	  
      'defines': [
        'ARCH="<(target_arch)"',
        'PLATFORM="<(OS)"',
		'_LARGEFILE_SOURCE',
		'_FILE_OFFSET_BITS=64',
      ],
	  
      'include_dirs': [
        '<(NODE_ROOT)/src',
        '<(NODE_ROOT)/deps/v8/include',
        '<(NODE_ROOT)/deps/uv/include',
      ],

      'conditions': [
        [ 'OS=="win"', {
          'defines': [
            'uint=unsigned int',
            'PLATFORM="win32"',
          ],
          'libraries': [ '-l<(NODE_ROOT)/<(node_lib_folder)/node.lib' ],
		  'msvs_configuration_attributes': {
              'OutputDirectory': 'build',
			  'IntermediateDirectory': 'build\\obj',
		  },
		  'msvs-settings': {
		    'VCLinkerTool': {
				'SubSystem': 3, # /subsystem:dll
		      },
		   },
        }]
      ],
    },
  ] # end targets
}

