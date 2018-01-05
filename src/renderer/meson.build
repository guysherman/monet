renderer_includes = include_directories('include')
renderer_sources = [
	'src/Renderer.cxx',
	'src/Geometry.cxx',
	'src/ShaderProgram.cxx',
	'src/Texture.cxx',
	'src/SimpleRenderPass.cxx'
]
renderer_deps = []
renderer_deps += dependency('glew')
renderer_deps += dependency('glm')
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

