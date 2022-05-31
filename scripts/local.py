# -*- coding: utf-8 -*-

"""Additional scripts for local builds

"""
import os
import subprocess
from scripts.utils import get_build_config, get_build_dir


def run(target):
  """Run command - Run the pre-built program

  Args:
      target (str): Build target name

  Returns:
      int: sys exit code
  """
  print(f'Running target={target}')

  config = get_build_config(target)
  build_path = get_build_dir(target)
  output_name = config['OUTPUT_NAME']
  output_file = f'{output_name}'
  output_path = os.path.join(build_path, output_file)

  result = subprocess.run(output_path)
  return result.returncode
