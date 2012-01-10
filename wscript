from os import unlink, symlink, popen
from os.path import exists


def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.check_cfg(package='gtk+-2.0', args='--cflags --libs', uselib_store='GTK',)
  conf.check_cfg(package='glib-2.0', args='--cflags --libs', uselib_store='GLIB')
  conf.check_cfg(package='webkit-1.0', args='--cflags --libs', uselib_store='WEBKIT')
        
def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "WebKitWindow"
  obj.find_sources_in_dirs("src")
  obj.uselib = "GTK GLIB WEBKIT"
      
def shutdown():
  if not exists('WebKitWindow.node'):
    if exists('build/Release/WebKitWindow.node'):
      symlink('build/Release/WebKitWindow.node', 'WebKitWindow.node')
