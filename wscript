from os import unlink, symlink, popen
from os.path import exists


def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.check_cfg(package='QtCore', args='--cflags --libs', uselib_store='QtCore', mandatory=True)
  conf.check_cfg(package='QtGui', args='--cflags --libs', uselib_store='QtGui', mandatory=True)
  conf.check_cfg(package='QtWebKit', args='--cflags --libs', uselib_store='QtWebKit', mandatory=True)
        
def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.cxxflags = ['-DQT_NO_DEBUG', '-DQT_GUI_LIB', '-DQT_CORE_LIB', '-DQT_SHARED']
  obj.target = "WebKitWindow"
  obj.find_sources_in_dirs("src")
  obj.uselib = "QtCore QtGui QtWebKit"
      
def shutdown():
  if not exists('WebKitWindow.node'):
    if exists('build/Release/WebKitWindow.node'):
      symlink('build/Release/WebKitWindow.node', 'WebKitWindow.node')
