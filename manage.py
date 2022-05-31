#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import logging
from scripts import builder, utils

# main command methods
def help():
  """Help command.

  Returns:
      int: sys exit code
  """

  targets = utils.get_targets()
  target_list = '\n    '.join(sorted(targets))

  script_sets = utils.get_scripts()
  method_lists = {
    name: utils.get_script_set(name) for name in script_sets
  }

  print(f'''
C/C++ Template Project - Build Tool

  Usage:
    python3 manage.py COMMAND [ ARGS ] [ OPTIONS ]

  Commands [ args ]:
    help                           Show this help message
    docs                           Build docs with Doxygen
    clean [ TARGET ]               Clean the build directory Default: clean all
    build [ TARGET ]               Build one or all targets Default: build all
    script  TYPE  NAME  [ ARGS]    Run a custom script (see "Custom Scripts")

  Options:
    -d, --debug         Enable debug logging

  Targets:
    {target_list}

  Custom Scripts:'''.format())

  for script_type, commands in method_lists.items():
    print(f'    {script_type}')
    for command,info in commands.items():
      print(f'      {command} {info["args"]}')

  return 0


def run_script(source, method, *args):
  """Run a custom (platform-specific) script

  Args:
      source (str): script source
      method (str): method to run
      args (list): list of script args

  Returns:
      int: sys exit code
  """

  # get script info
  script_sets = utils.get_scripts()
  if source not in script_sets:
    print(f'Unknown script type: {source}')
    return 1

  script_set = utils.get_script_set(source)

  # check script exists
  if method not in script_set:
    print(f'Unknown script method: {method}')
    return 1

  # get script method
  script_method = script_set[method]['method']

  # run script
  result = script_method(*args)

  # return result
  return result


# collect list of command methods
COMMANDS = {
  'help': help,
  'docs': builder.docs,
  'clean': builder.clean,
  'build': builder.build,
  'script': run_script
}


def main(args=[]):
  """Main entry point for the script.

  Args:
      args (list, optional): list of command line args, with the first command (script name) dropped. Defaults to [].

  Returns:
      int: sys exit code
  """

  # define default command / args / options
  log_lvl = logging.INFO
  command = None
  command_args = []
  command_options = {}

  # collect user args
  for arg in args:

    # check for options
    if arg in ('-d', '--debug'):
      log_lvl = logging.DEBUG

    # check for command if not yet set
    elif command is None:
      if arg in COMMANDS:
        command = COMMANDS[arg]
      else:
        print(f'Unknown command: {arg}')
        return 1
    
    # command set, not a known option, assume positional arg
    else:
      command_args.append(arg)

  
  logging.basicConfig(format='[%(asctime)s] %(message)s', level=log_lvl)

  # default to help command
  if command is None:
    command = help

  # run command
  result = command(*command_args, **command_options)

  # return result
  return result


# run main if called directly
if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
  