ui_includes = include_directories('include')
ui_sources = [
	'src/gtk/MainWindow-gtk.cxx'
]
ui_deps = []
ui_deps += dependency('gtkmm-3.0')
ui_deps += dependency('glew')
ui_lib = static_library('ui', ui_sources, dependencies : ui_deps)
ui_module = declare_dependency(link_with : ui_lib, include_directories : ui_includes)

dependencies += ui_deps
dependencies += ui_module
