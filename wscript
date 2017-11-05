#! /usr/bin/env python
# encoding: utf-8
# Guy Sherman, 2015

import subprocess
import waftools
import sys

PROJ_VERSION			=	'0.0.1'
PROJ_MAJOR_VERSION 	=	'0'


VERSION = PROJ_VERSION
APPNAME = 'monet'

top = '.'
out = 'build'



defines = ''


SUBFOLDERS = ['dep', 'src']

def options(opt):
	opt.recurse(SUBFOLDERS)

	opt.load('compiler_cxx')
	opt.load('cppcheck', tooldir=waftools.location)
#	opt.add_option("--shared", action="store_true", help="build shared library")
#	opt.add_option("--static", action="store_true", help="build static library")


def configure(conf):
	env = conf.env
	conf.recurse(SUBFOLDERS)
	conf.setenv('main', env)
	conf.load('compiler_cxx')
	conf.load('cppcheck')
	if sys.platform == 'darwin':
		conf.env.LIBPATH_BOOST = ['/usr/local/lib']
		conf.env.INCLUDES_BOOST = ['/usr/local/include']
		conf.env.LIBPATH_TGA = ['/usr/local/lib']
		conf.env.INCLUDES_TGA = ['/usr/local/include']
	else:
		conf.env.LIBPATH_BOOST = ['/usr/lib']
		conf.env.INCLUDES_BOOST = ['/usr/include']
		conf.env.LIBPATH_TGA = ['/usr/lib']
		conf.env.INCLUDES_TGA = ['/usr/include']



def build(bld):
	bld.recurse(SUBFOLDERS)
	bld.env = bld.all_envs['main']
	bld.program(source = bld.path.ant_glob('tests/**/*.cxx'),
				includes = ['./include', './src', './dep/wq/include'],
				cxxflags=['-w'],
				lib = ['pthread', 'boost_system'],
				target = 'tests/all',
				install_path = '${BINDIR}',
				defines = defines,
				use=['wq', 'gtest', 'gtest_main', 'BOOST', 'renderer'],
				cppcheck_skip=True,
				features="cxx cxxprogram")


def test(bld):
	subprocess.check_call("./run_tests.sh")


def verify(bld):
	subprocess.check_call("./grind_tests.sh")
