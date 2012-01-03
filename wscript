VERSION = "0.0.1"


def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

  #if not conf.env.LIB_QTWEBKIT: conf.fatal('QtWebKit not found - Semantik requires Qt >= 4.4')
    
  #if not conf.check(lib="libqtwebkit4", mandantory=True): conf.fatal("libqtwebkit4 not found on this system.")
        
def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")

  # Will generate build/default/pane.node
  obj.target = "pane"

  # compile all files in the src/ directory
  obj.find_sources_in_dirs("src")

# This is so that we have pane.node in the root
# rather than doing require('./build/default/pane.node')
def shutdown(bld):
  # HACK to get binding.node out of build directory.
  # better way to do this?
  if Options.commands['clean']:
    if exists('pane.node'): unlink('pane.node')
  else:
    if exists('build/default/pane.node') and not exists('pane.node'):
      symlink(getcwd()+'/build/default/pane.node', 'pane.node')
