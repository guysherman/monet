util_includes = include_directories('include')
util_sources = [
    'src/File.cxx'
]

util_deps = []

util_link_args = []
if host_machine.system() == 'darwin'
endif

util_lib = static_library('util', util_sources, dependencies : util_deps)
util_module = declare_dependency(link_with : util_lib, include_directories : util_includes)

dependencies += util_deps
dependencies += util_module
link_args += util_link_args

