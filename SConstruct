#!/usr/bin/python

env = Environment()
env.Append(CPPPATH = ['-I./include', '-I./deps'])
env.Append(CCFLAGS = ['-ggdb3', '-std=c++11'])
env.Library('lib/packagemanager', Glob('src/*.cpp'))

SConscript(['./deps/tinyxml/SConscript'])

env.Append(LIBPATH = ['./lib', './deps/tinyxml'])
env.Append(LIBS = ['packagemanager', 'tinyxml', 'dl'])
env.Program('bin/demo', Glob('demo/*.cpp'))
env.SharedLibrary('bin/commpackage', Glob('demo/packages/*.cpp'))
