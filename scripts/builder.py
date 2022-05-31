# -*- coding: utf-8 -*-

"""Internal build tools

"""

import os
import shutil
import subprocess
from scripts.utils import *


TEMPLATE_MAKEFILE = os.path.join('config', 'template.mk')


def build(target='all'):
  """Build command.

  Args:
      target (str, optional): Build target name (default: all).

  Returns:
      int: sys exit code
  """
  # iterate through all targets if 'all' set
  if target == 'all':
    targets = get_targets()
    for t in targets:
      build(t)
    return 0
  
  print(f'Building target={target}')
  temp_files = {
    'makefile': 'tmp.mk'
  }

  try:

    # get build config
    config = get_build_config(target)

    # parse out various file types
    c_input_files = filter(lambda f: f.endswith('.c'), config['SRC_FILES'])
    cxx_input_files = filter(lambda f: f.endswith('.cc') or f.endswith('.cpp'), config['SRC_FILES'])
    as_input_files = filter(lambda f: f.lower().endswith('.s'), config['SRC_FILES'])
    ld_input_files = filter(lambda f: f.endswith('.ld'), config['SRC_FILES'])

    # setup build environment
    make_variables = {
      'BUILD_PATH': get_build_dir(target),
      'OUTPUT_NAME': config['OUTPUT_NAME'],
      'OUTPUT_VARIANTS': ' '.join(config['OUTPUT_VARIANTS']),
      'C_CMD': config['C_CMD'],
      'CXX_CMD': config['CXX_CMD'],
      'AS_CMD': config['AS_CMD'],
      'LD_CMD': config['LD_CMD'],
      'OBJCOPY_CMD': config['OBJCOPY_CMD'],
      'OBJDUMP_CMD': config['OBJDUMP_CMD'],
      'C_INPUT_FILES':  ' '.join(c_input_files),
      'CXX_INPUT_FILES':  ' '.join(cxx_input_files),
      'AS_INPUT_FILES':  ' '.join(as_input_files),
      'LD_INPUT_FILES':  ' '.join(ld_input_files),
      'C_FLAGS':  ' '.join(config['C_FLAGS']),
      'CXX_FLAGS':  ' '.join(config['CXX_FLAGS']),
      'AS_FLAGS':  ' '.join(config['AS_FLAGS']),
      'LD_FLAGS':  ' '.join(config['LD_FLAGS']),
    }

    # generate makefile
    _generate_makefile(temp_files['makefile'], **make_variables)

    # build
    subprocess.run(['make', '-f', temp_files['makefile']])

  finally:
    # cleanup temp files
    for temp_file in temp_files.values():
      print(f'Removing temp file: {temp_file}')
      try:
        os.remove(temp_file)
      except FileNotFoundError:
        pass


  return 0


def clean(target='all'):
  """Clean command - Clean the build directory for the specified platform and application.

  Args:
      platform (str, optional): See PLATFORMS (default: all).
      application (str, optional): See APPLICATIONS (default: all).
      release (str, optional): See RELEASES. Defaults to 'debug'.

  Returns:
      int: sys exit code
  """

  if target == 'all':
    print('Cleaning all targets')
    config = get_project_config()
    build_path = config['BUILD_DIR']
  else:
    print(f'Cleaning target "{target}"')
    config = get_build_config(target)
    build_path = get_build_dir(target)

  print(f'Removing dir: {build_path}')
  shutil.rmtree(build_path)
  return 0


def docs():
  """Build Doxygen documentation
  
  Returns:
      int: sys exit code
  """
  # run doxygen
  result = subprocess.run(['doxygen', 'doxygen.conf'])

  # return result
  return result


def _generate_makefile(output, template_file=TEMPLATE_MAKEFILE, **template_values):

  # read in template file
  with open(template_file) as f:
    template = f.read()

  # render template
  rendered = template.format(**template_values)

  # write output file
  with open(output, 'w') as f:
    f.write(rendered)
  