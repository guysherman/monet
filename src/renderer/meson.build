renderer_includes = include_directories('include')
renderer_sources = [
	'src/Renderer.cxx',
	'src/Geometry.cxx',
	'src/ShaderProgram.cxx',
	'src/Texture.cxx',
	'src/DemosaicRenderPass.cxx'
]
renderer_deps = []
renderer_deps += dependency('glew')
renderer_deps += dependency('glm')
renderer_deps += dependency('rawspeed')

code = '''#include<stdio.h>
#include <pugixml.hpp>
#include <pugiconfig.hpp>
void func() { printf("Compile me.\n"); }
int main(int argc, char **argv) {return 0;}
'''
compiler = meson.get_compiler('cpp')
pugi_headers_exist = compiler.compiles(code, name : 'pugixml headers')
pugi_lib_exists = compiler.links(code, args: '-lpugixml', name: 'pugxml lib')

if not (pugi_headers_exist and pugi_lib_exists)
	error('pugixml seems to be missing!')
endif

pugi_xml = declare_dependency(link_args: '-lpugixml')
renderer_deps += pugi_xml
renderer_deps += util_module

renderer_link_args = []
if host_machine.system() == 'darwin'
	renderer_link_args += ['-framework', 'GLUT', '-framework', 'OpenGL']
endif

renderer_lib = static_library('renderer', renderer_sources, dependencies : renderer_deps, cpp_pch: ['pch/pch.h', 'pch/pch.cpp'])
renderer_module = declare_dependency(link_with : renderer_lib, include_directories : renderer_includes)

dependencies += renderer_deps
dependencies += renderer_module
link_args += renderer_link_args

