# -*- coding: utf-8 -*-

MODULE_PATH = 'scripts.nrf52'
SCRIPTS = [
  {
    'name': 'readregs',
    'args': '',
    'brief': 'Read registers from the attached device'
  },
  {
    'name': 'flash',
    'args': 'TARGET [ VARIANT ]',
    'brief': 'Flash a pre-build binary to the attached device'
  },
  {
    'name': 'reset',
    'args': '',
    'brief': 'Reset the attached device'
  },
  {
    'name': 'erase',
    'args': '',
    'brief': 'Erase the attached device'
  },
  # {
  #   'name': 'flash_sd',
  #   'args': '[ SD_VERSION ]',
  #   'brief': 'Flash a softdevice to the attached device'
  # }
]