# -*- coding: utf-8 -*-

"""Project Configuration

This file is used to define important directory paths and build configurations.
Additional config files are required for each platform, application, release,
and targe; these should be stored in the corresponding sub-folders. Template
config files are provided in these directories to demonstrate required
variables.
"""


# define high-level project directory structure
BUILD_DIR = 'build'
SRC_DIR = 'src'

# common args for all targets
C_FLAGS = [
  '-std=c17',
  '-Wall',
  '-Wextra',
  '-Werror'
]
CXX_FLAGS = [
  '-std=c++17',
  '-Wall',
  '-Wextra',
  '-Werror'
]
AS_FLAGS = []
LD_FLAGS = []

SRC_FILES=[]
INC_DIRS = [
  SRC_DIR
]

MAKE_VARS = {}
MAKE_INCLUDES = []
