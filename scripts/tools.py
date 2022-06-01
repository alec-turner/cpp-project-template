#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""Tools to help with development

"""

import sys
import os


def parse_makefile(makefile_path, prefix=None, output=None):
  print(f'Getting source from makefile "{makefile_path}" (prefix="{prefix}")')

  src_list = ''
  inc_list = ''

  src_files = False
  inc_dirs = False

  with open(makefile_path) as f:

    for line in f:
      line = line.strip()
      if line.endswith('\\'):
        line = line[:-1].strip()

      if src_files:
        if not line:
          src_files = False
          continue

        if not line.startswith('$(SDK_ROOT)'):
          continue
        line = line[12:]
        line = line.split('/')
        item = 'os.path.join('
        if prefix:
          item += f'{prefix}, '
        item += ', '.join(f"'{i}'" for i in line)
        item += ')'
        src_list += f'  {item},\n'


      elif inc_dirs:
        if not line:
          inc_dirs = False
          continue

        if not line.startswith('$(SDK_ROOT)'):
          continue
        line = line[12:]
        line = line.split('/')
        item = 'os.path.join('
        if prefix:
          item += f'{prefix}, '
        item += ', '.join(f"'{i}'" for i in line)
        item += ')'
        inc_list += f'  {item},\n'

      elif line.startswith('SRC_FILES +='):
        src_files = True

      elif line.startswith('INC_FOLDERS +='):
        inc_dirs = True


  if output:
    with open(output, 'w') as f:
      f.write('SRC_FILES = [\n')
      f.write(src_list)
      f.write(']\n\n')
      f.write('INC_FOLDERS = [\n')
      f.write(inc_list)
      f.write(']\n')

  else:
    print('SRC_FILES = [')
    print(src_list)
    print(']')
    print()
    print('INC_DIRS = [')
    print(inc_list)
    print(']')

  return 0


COMMANDS = {
  'parse_makefile': parse_makefile
}

def main(args=[]):

  help_msg = '''
Template Project - Command Line Tools

  Usage: python3 tools.py COMMAND [ ARGS ] [ OPTIONS ]

Commands:

  parse_makefile MAKEFILE_PATH [ PREFIX ] [ OUTPUT ]     Parse src and inc lists from an nRF Makefile

'''

  command = None
  pargs = []
  kwargs = {}

  for arg in args:
    if '=' in arg:
      k, v = arg.split('=', maxsplit=1)
      kwargs[k] = v
    elif command is None:
      command = arg
    else:
      pargs.append(arg)
  
  if command in (None, 'help', '-h', '--help'):
    print(help_msg)
    return 0
  
  elif command not in COMMANDS:
    print(f'Unknown command "{command}"')
    return 1
  
  else:
    return COMMANDS[command](*pargs, **kwargs)


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))