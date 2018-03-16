deps_dir = meson.current_source_dir()
rawspeed_lib_path = join_paths(deps_dir, 'rawspeed/build/src')

rawspeed_include_dirs = include_directories(['rawspeed/src/librawspeed','rawspeed/src/external', 'rawspeed/build/src'])
rawspeed_dep = declare_dependency(link_args : ['-L'+rawspeed_lib_path, '-lrawspeed', '-pthread'],
  include_directories : rawspeed_include_dirs)