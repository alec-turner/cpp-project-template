# -*- coding: utf-8 -*-

RELEASE_NAME = 'debug'
RELEASE_BRIEF = 'Include debugging information in build'
RELEASE_DESCRIPTION = '''
Debug-level release suitable for use with common debugging tools. Optimisations
are limited compared to a production build.
'''

C_FLAGS = ['-O3']
CXX_FLAGS = ['-O3']
AS_FLAGS = []
LD_FLAGS = []

SRC_FILES = []
INC_DIRS = []

MAKE_VARS = {}
MAKE_INCLUDES = []