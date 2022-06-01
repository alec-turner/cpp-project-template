# -*- coding: utf-8 -*-

PLATFORM_NAME = 'local'
PLATFORM_BRIEF = 'Local (Linux 64-bit) platform'
PLATFORM_DESCRIPTION = '''
Local development platform (Linux 64-bit).

TODO: either make more options for various "local" platforms or dynamically
detect system and use appropriate settings.
'''

C_CMD = 'gcc'
CXX_CMD = 'g++'
AS_CMD = ''
LD_CMD = 'g++'
OBJCOPY_CMD = 'objcopy'
OBJDUMP_CMD = 'objdump'

C_FLAGS = []
CXX_FLAGS = []
AS_FLAGS = []
LD_FLAGS = []

SRC_FILES = []
INC_DIRS = []

MAKE_VARS = {}
MAKE_INCLUDES = []
