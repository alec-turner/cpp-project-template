# -*- coding: utf-8 -*-
import os
import re

APPLICATION_NAME = 'unittest'
APPLICATION_BRIEF = 'Unit testing app'
APPLICATION_DESCRIPTION = '''
# Unittest Application
Unittesting application based on the cppunit library
'''

C_FLAGS = []
CXX_FLAGS = []
AS_FLAGS = []
LD_FLAGS = [
  '-lcppunit'
]

SRC_FILES = [
  'src/application/unittest/main.cc'
]
# collect any files with a *_test.cc or *_test.cpp suffix
for root,_,files in os.walk('src'):
  for file in files:
    if file.endswith('_test.cc') or file.endswith('_test.cpp'):
      SRC_FILES.append(os.path.join(root, file))

INC_DIRS = []

MAKE_VARS = {}
MAKE_INCLUDES = []