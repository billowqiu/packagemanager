#!/usr/bin/python

env = Environment()
env.Append(CCFLAGS = ['-I./include', '-ggdb3', '-std=c++0x'])
env.Library('lib/packagemanager', Glob('src/*.cpp'))

env.Append(LIBPATH = ['lib', '/usr/local/lib'])
env.Append(LIBS = ['packagemanager', 'tinyxml'])
env.Program('bin/demo', Glob('demo/*.cpp'))
env.SharedLibrary('bin/commpackage', Glob('demo/packages/*.cpp'))
#env_packages = Environment()
