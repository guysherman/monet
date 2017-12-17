project('monet-photo', 'cpp')
add_global_arguments(['-std=c++14', '-Wno-c++11-extensions', '-Wno-c++14-extensions'], language : 'cpp')


dependencies = []
link_args = []

subdir('src/ui')

executable('monet-photo', 'src/app/main.cxx', dependencies: dependencies, link_args: link_args)
