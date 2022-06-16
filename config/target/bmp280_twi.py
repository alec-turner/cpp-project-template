# -*- coding: utf-8 -*-

import os

linker_script = os.path.join('res', 'pca10040_nosd.ld')
sdk_path = os.path.join('lib', 'nRF5_SDK_17.1.0')

TARGET_NAME = 'bmp280_twi'
TARGET_BRIEF = 'Example BMP280 Application for nRF5DK using TWI/I2C'
TARGET_DESCRIPTION = '''
Example application using the nRF5DK and Bosch BMP280 pressure, temperature
sensor. The application uses the PCA10040's TWI interface.
'''

APPLICATION='bmp280'
PLATFORM='pca10040'
RELEASE='debug'

OUTPUT_NAME='bmp280_twi'
OUTPUT_VARIANTS=[
  'hex',
  'bin',
  'elf',
  'map'
]

C_FLAGS = [
  '-DNRFX_TWI_ENABLED=1',
  '-DNRFX_TWI0_ENABLED=1',
  '-DNRFX_TWI_DEFAULT_CONFIG_FREQUENCY=26738688',
  '-DNRFX_TWI_DEFAULT_CONFIG_HOLD_BUS_UNINIT=0',
  '-DNRFX_TWI_DEFAULT_CONFIG_IRQ_PRIORITY=6'
]
CXX_FLAGS = [
  '-DBMP280_USE_TWI=1',
  '-DNRFX_TWI_ENABLED=1',
  '-DNRFX_TWI0_ENABLED=1',
  '-DNRFX_TWI_DEFAULT_CONFIG_FREQUENCY=26738688',
  '-DNRFX_TWI_DEFAULT_CONFIG_HOLD_BUS_UNINIT=0',
  '-DNRFX_TWI_DEFAULT_CONFIG_IRQ_PRIORITY=6'
]

AS_FLAGS = []
LD_FLAGS = [
  f'-T{linker_script}',
]

SRC_FILES = [
  os.path.join('src', 'platform', 'pca10040', 'twi', 'twi_driver.cc'),
  os.path.join('src', 'platform', 'pca10040', 'bmp280', 'bmp280_twi.cc'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'drivers', 'src', 'nrfx_twi.c'),
]
INC_DIRS = []

MAKE_VARS = {}
MAKE_INCLUDES = []
