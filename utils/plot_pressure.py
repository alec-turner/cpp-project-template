#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
File: python3_script.py
Author: Alec Turner <alec.turner8@gmail.com>

"""
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from scipy.signal import butter, filtfilt

def exp_filter(signal, alpha):
  filtered = [ signal[0] ]
  for i in range(1, len(signal)):
    filtered.append(alpha * signal[i] + (1-alpha) * filtered[i-1])
  return filtered


def butter_filter(signal, cutoff, fs=1, order=4):
  nyq = 0.5 * fs
  normal_cutoff = cutoff / nyq
  b, a = butter(order, normal_cutoff, btype='low', analog=False)
  filtered = filtfilt(b, a, signal)
  return filtered


def plot_log(filename):

  # load data from file and clean up
  data = pd.read_csv(filename)
  data.columns = ['timestamp', 'temperature', 'pressure']
  data['timestamp'] = pd.to_datetime(data['timestamp'])
  data['time'] = (data['timestamp'] - data['timestamp'].iloc[0]).dt.total_seconds()
  data['pressure'] *= 0.001
  print(data)

  dt = data['time'].diff().mean()
  fs = 1./dt

  # apply filtering
  alpha = 0.2
  data['temperature_exp'] = exp_filter(data['temperature'], alpha)
  data['pressure_exp'] = exp_filter(data['pressure'], alpha)

  cutoff = 0.5
  data['temperature_butter'] = butter_filter(data['temperature'], cutoff=cutoff, fs=fs)
  data['pressure_butter'] = butter_filter(data['pressure'], cutoff=cutoff, fs=fs)

  # plot data
  fig = plt.figure(figsize=(10,5))
  
  ax1 = plt.subplot(2,1,1)
  ax1.plot(data['time'], data['temperature'], marker='.', markersize=3, linewidth=3, label='Raw')
  ax1.plot(data['time'], data['temperature_exp'], linewidth=2, alpha=0.7, label=f'Exp. Filter (alpha={alpha})')
  ax1.plot(data['time'], data['temperature_butter'], linewidth=2, alpha=0.7, label=f'BW Filter (cutoff={cutoff})')
  ax1.legend(loc='upper left', bbox_to_anchor=(1.05, 1))
  ax1.grid()
  ax1.set_xlabel('Time (s)')
  ax1.set_ylabel('Temperature (C)')

  ax2 = plt.subplot(2,1,2)
  ax2.plot(data['time'], data['pressure'], marker='.', markersize=3, linewidth=3, label='Raw')
  ax2.plot(data['time'], data['pressure_exp'], linewidth=2, alpha=0.7, label=f'Exp. Filter (alpha={alpha})')
  ax2.plot(data['time'], data['pressure_butter'], linewidth=2, alpha=0.7, label=f'BW Filter (cutoff={cutoff})')
  ax2.legend(loc='upper left', bbox_to_anchor=(1.05, 1))
  ax2.grid()
  ax2.set_xlabel('Time (s)')
  ax2.set_ylabel('Pressure (kPa)')

  fig.tight_layout()
  plt.show()


def main(args=[]):
  """
Main method for the python3_script template script. Collects user args and
(optionally) prints a basic help message.

"""


  # define help message
  help_msg = '''
Plotting utility for the SPI example; plots logs from log_pressure.py

Usage: python3 plot_pressure.py FILENAME [ OPTIONS ]

OPTIONS
  -h, --help

'''

  # default args
  filename = None

  # collect user args  
  for arg in args:

    if arg in ('-h', '--help', 'help'):
      print(help_msg)
      return 0
      
    elif filename is None:
      filename = arg
      
    else:
      raise Exception(f'Invalid arg "{arg}"')


  # Do something with the data
  if not filename:
    print(help_msg)
    return 0


  plot_log(filename)


  # return exit code
  return 0


if __name__ == '__main__':
  import sys
  result = main(sys.argv[1:])
  sys.exit(result)
  
