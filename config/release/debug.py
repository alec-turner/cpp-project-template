# -*- coding: utf-8 -*-

RELEASE_NAME = 'debug'
RELEASE_BRIEF = 'Include debugging information in build'
RELEASE_DESCRIPTION = '''
Debug-level release suitable for use with common debugging tools. Optimisations
are limited compared to a production build.
'''

C_FLAGS = ['-Og', '-g']
CXX_FLAGS = ['-Og', '-g', '-DDEBUG=1']
AS_FLAGS = []
LD_FLAGS = []

SRC_FILES = []
INC_DIRS = []

MAKE_VARS = {}
MAKE_INCLUDES = []