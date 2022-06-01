# -*- coding: utf-8 -*-

TARGET_NAME = 'blinky'
TARGET_BRIEF = 'Basic blinky example for nRF5DK'
TARGET_DESCRIPTION = '''
The basic blinky application built for the nRF5DK.
'''

APPLICATION='blinky'
PLATFORM='pca10040'
RELEASE='debug'

OUTPUT_NAME='blinky'
OUTPUT_VARIANTS=[
  'hex',
  'bin',
  'elf',
  'map'
]

C_FLAGS = []
CXX_FLAGS = []
AS_FLAGS = []
LD_FLAGS = []

SRC_FILES = []
INC_DIRS = []

MAKE_VARS = {}
MAKE_INCLUDES = []