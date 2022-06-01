# -*- coding: utf-8 -*-

"""Additional scripts for local builds

"""
import os
import subprocess
from scripts.utils import get_build_config, get_build_dir


def run(target, *args):
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

  cmd_args = [output_path] + list(args)
  cmd_string = ' '.join(cmd_args)
  print(f'cmd="{cmd_string}"')
  print()
  result = subprocess.run(cmd_args)
  return result.returncode
