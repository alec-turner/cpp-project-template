# -*- coding: utf-8 -*-
import os

APPLICATION_NAME = 'i2c_example'
APPLICATION_BRIEF = 'Example I2C Application'
APPLICATION_DESCRIPTION = '''
I2C example application using the Bosch BME280 pressure, temperature and
humidity sensor.
'''

C_FLAGS = []
CXX_FLAGS = []
AS_FLAGS = []
LD_FLAGS = []

SRC_FILES = [
  os.path.join('src', 'application', 'i2c', 'main.cc')
]
INC_DIRS = [
  os.path.join('src', 'application', 'i2c'),
]

MAKE_VARS = {}
MAKE_INCLUDES = []