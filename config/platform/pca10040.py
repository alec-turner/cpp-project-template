# -*- coding: utf-8 -*-

import os
from scripts.utils import get_toolchain_info

toolchain_prefix = 'arm-none-eabi'
toolchain_info = get_toolchain_info(toolchain_prefix, 'gcc')
toolchain_args = f'GNU_PREFIX={toolchain_info["prefix"]} GNU_INSTALL_ROOT={toolchain_info["path"]} GNU_VERSION={toolchain_info["version"]}'

sdk_dir = os.path.join('lib', 'nRF5_SDK_17.1.0')

PLATFORM_NAME = 'pca10040'
PLATFORM_BRIEF = 'nRF5DK - PCA10040'
PLATFORM_DESCRIPTION = '''
Nordic Semiconductor nRF5DK development kit (PCA10040)
'''

# Note: Makefile.common assigns variables for these
# C_CMD = 'CC'
# CXX_CMD = 'CXX'
# AS_CMD = 'AS'
# LD_CMD = 'LD'
# OBJCOPY_CMD = 'OBJCOPY'
# OBJDUMP_CMD = 'OBJDUMP'
C_CMD = 'arm-none-eabi-gcc'
CXX_CMD = 'arm-none-eabi-g++'
AS_CMD = 'arm-none-eabi-g++'
LD_CMD = 'arm-none-eabi-g++'
OBJCOPY_CMD = 'arm-none-eabi-objcopy'
OBJDUMP_CMD = 'arm-none-eabi-objdump'

C_FLAGS = [
  '-DBOARD_PCA10040',
  '-DFLOAT_ABI_HARD',
  '-DNRF52',
  '-DNRF52832_XXAA',
  '-DNRF52_PAN_74',
  '-mcpu=cortex-m4',
  '-mthumb',
  '-mabi=aapcs',
  '-mfloat-abi=hard',
  '-mfpu=fpv4-sp-d16',
  '-ffunction-sections',
  '-fdata-sections',
  '-fno-strict-aliasing',
  '-fno-builtin',
  '-fshort-enums',
  '-D__HEAP_SIZE=8192',
  '-D__STACK_SIZE=8192',
]
CXX_FLAGS = [
  '-DBOARD_PCA10040',
  '-DFLOAT_ABI_HARD',
  '-DNRF52',
  '-DNRF52832_XXAA',
  '-DNRF52_PAN_74',
  '-mcpu=cortex-m4',
  '-mthumb',
  '-mabi=aapcs',
  '-mfloat-abi=hard',
  '-mfpu=fpv4-sp-d16',
  '-ffunction-sections',
  '-fdata-sections',
  '-fno-strict-aliasing',
  '-fno-builtin',
  '-fshort-enums',
  '-D__HEAP_SIZE=8192',
  '-D__STACK_SIZE=8192',
]
AS_FLAGS = [
  '-mcpu=cortex-m4',
  '-mthumb',
  '-mabi=aapcs',
  '-mfloat-abi=hard',
  '-mfpu=fpv4-sp-d16',
  '-DBOARD_PCA10040',
  '-DFLOAT_ABI_HARD',
  '-DNRF52',
  '-DNRF52832_XXAA',
  '-DNRF52_PAN_74',
  '-D__HEAP_SIZE=8192',
  '-D__STACK_SIZE=8192',
  '-x',
  'assembler-with-cpp'
]
LD_FLAGS = [
  '-mthumb',
  '-mabi=aapcs',
  '-L' + os.path.join(sdk_dir, 'modules', 'nrfx', 'mdk'),
  '-mcpu=cortex-m4',
  '-mfloat-abi=hard',
  '-mfpu=fpv4-sp-d16',
  '-Wl,--gc-sections',
  '--specs=nano.specs'
]
SRC_FILES = []
INC_DIRS = []

MAKE_VARS = {
  'TEMPLATE_PATH': os.path.join(sdk_dir, 'components', 'toolchain', 'gcc'),
  'GNU_PREFIX': toolchain_info['prefix'],
  'GNU_INSTALL_ROOT': toolchain_info['path'] + os.sep,
  'GNU_VERSION': toolchain_info['version'],
}
MAKE_INCLUDES = [
  os.path.join(sdk_dir, 'components', 'toolchain', 'gcc', 'Makefile.common')
]