project('monet-photo', 'cpp')
cpp_args = ['-std=c++14', '-Wno-c++11-extensions', '-Wno-c++14-extensions']
isDebug = get_option('debug')
if isDebug == true
    cpp_args += '-ggdb'
endif
add_global_arguments(cpp_args, language : 'cpp')


dependencies = []
link_args = []

subdir('src/renderer')
subdir('src/ui')


executable('monet-photo', 'src/app/main.cxx', dependencies: dependencies, link_args: link_args)
