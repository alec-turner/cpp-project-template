#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
File: python3_script.py
Author: Alec Turner <alec.turner8@gmail.com>

"""
from datetime import datetime
import serial


def start_logging(verbose=False, output=None):
  with serial.Serial('/dev/ttyACM0', 115200) as ser:
    while True:
      line = ser.readline()
      dt = datetime.now()
      ts = dt.isoformat()
      try:
        line = line.decode('utf-8')
        line = line.strip()
        t,p = line.split(' ')[-1].split(',')
        t = float(t)
        p = float(p)

        formatted = f'{ts},{t},{p}'
        if line:
          if verbose:
            print(formatted)
          if output:
            with open(output, 'a') as f:
              f.write(f'{formatted}\n')


      except Exception:
        print('Error parsing line:', line)
        continue



def main(args=[]):
  """
Main method for the python3_script template script. Collects user args and
(optionally) prints a basic help message.

"""


  # define help message
  help_msg = '''
Logging utility for the SPI example, assuming connection to the BMP280
Pressure/Temperature sensor

Usage: python3 log_pressure.py [ OPTIONS ]

OPTIONS
  -h, --help
  -v, --verbose          Print messages, status to stdout
  output=LOG_FILE        Log file path to save output

'''

  # default args
  verbose = False
  output = None

  # collect user args  
  for arg in args:

    if arg in ('-h', '--help', 'help'):
      print(help_msg)
      return 0
      
    elif arg in ('-v', '--verbose'):
      verbose = True
      
    elif arg.startswith('output='):
      output = arg.split('=',maxsplit=1)[1]
      
    else:
      raise Exception(f'Invalid arg "{arg}"')


  # Do something with the data
  if not output:
    verbose = True


  start_logging(verbose, output)


  # return exit code
  return 0


if __name__ == '__main__':
  import sys
  result = main(sys.argv[1:])
  sys.exit(result)
  
