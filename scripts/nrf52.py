# -*- coding: utf-8 -*-

"""Additional scripts for nRF52 builds

"""
import os
import subprocess
from scripts.utils import get_build_config, get_build_dir

def readregs():
  """Readregs command - Read registers from the attached device
  
  Args:

  Returns:
      int: sys exit code
  """
  result = subprocess.run(['nrfjprog', '-f' ,'NRF52', '--readregs'])
  return result.returncode


def flash(target, variant='hex'):
  """Flash command - Flash an application binary to a device.

  Args:
      target (str): Build target name

  Returns:
      int: sys exit code
  """
  print(f'Flashing target={target}')

  config = get_build_config(target)
  build_path = get_build_dir(target)
  output_name = config['OUTPUT_NAME']
  output_file = f'{output_name}.{variant}'
  output_path = os.path.join(build_path, output_file)

  result = subprocess.run(['nrfjprog', '-f', 'NRF52', '--program', output_path, '--sectorerase', '--reset'])
  return result.returncode


def erase():
  """Erase command - Erase flash for the attached device
  
  Args:

  Returns:
      int: sys exit code
  """
  result = subprocess.run(['nrfjprog', '-f' ,'NRF52', '--eraseall'])
  return result.returncode


def reset():
  """Reset command - Reset the attached device
  
  Args:

  Returns:
      int: sys exit code
  """
  result = subprocess.run(['nrfjprog', '-f' ,'NRF52', '-r'])
  return result.returncode