# -*- coding: utf-8 -*-

import os

sdk_path = os.path.join('lib', 'nRF5_SDK_17.1.0')

APPLICATION_NAME = 'bmp280'
APPLICATION_BRIEF = 'Basic BMP280 Pressure/Temperature Sensor Monitor'
APPLICATION_DESCRIPTION = '''
Example application using the Bosch BME280 pressure, temperature sensor with
the PCA10040's SPI or TWI interface.
'''


C_FLAGS = [
  '-DCONFIG_GPIO_AS_PINRESET',
  '-DAPP_TIMER_V2',
  '-DAPP_TIMER_V2_RTC1_ENABLED',
  '-Wno-expansion-to-defined',
  '-Wno-unused-parameter',
  '-Wno-unused-variable',
  '-Wno-missing-field-initializers',
]
CXX_FLAGS = [
  '-Wno-expansion-to-defined',
  '-Wno-unused-parameter',
  '-Wno-unused-variable',
  '-Wno-missing-field-initializers'
]
AS_FLAGS = [
  '-DBSP_DEFINES_ONLY',
  '-DCONFIG_GPIO_AS_PINRESET',
]
LD_FLAGS = []

SRC_FILES = [
  os.path.join('src', 'application', 'bmp280', 'pca10040_main.cc'),
  os.path.join('src', 'platform', 'pca10040', 'bmp280', 'bmp2.c'),
  os.path.join('src', 'platform', 'pca10040', 'bmp280', 'bmp280_driver.cc'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'mdk', 'gcc_startup_nrf52.S'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src', 'nrf_log_backend_rtt.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src', 'nrf_log_backend_serial.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src', 'nrf_log_backend_uart.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src', 'nrf_log_default_backends.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src', 'nrf_log_frontend.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src', 'nrf_log_str_formatter.c'),
  os.path.join(sdk_path, 'components', 'boards', 'boards.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'util', 'app_error.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'util', 'app_error_handler_gcc.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'util', 'app_error_weak.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'util', 'app_util_platform.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'util', 'nrf_assert.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'atomic_fifo', 'nrf_atfifo.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'atomic', 'nrf_atomic.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'balloc', 'nrf_balloc.c'),
  os.path.join(sdk_path, 'external', 'fprintf', 'nrf_fprintf.c'),
  os.path.join(sdk_path, 'external', 'fprintf', 'nrf_fprintf_format.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'memobj', 'nrf_memobj.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'ringbuf', 'nrf_ringbuf.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'sortlist', 'nrf_sortlist.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'strerror', 'nrf_strerror.c'),
  os.path.join(sdk_path, 'integration', 'nrfx', 'legacy', 'nrf_drv_uart.c'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'soc', 'nrfx_atomic.c'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'drivers', 'src', 'nrfx_gpiote.c'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'drivers', 'src', 'prs', 'nrfx_prs.c'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'drivers', 'src', 'nrfx_uart.c'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'drivers', 'src', 'nrfx_uarte.c'),
  os.path.join(sdk_path, 'components', 'libraries', 'bsp', 'bsp.c'),
  os.path.join(sdk_path, 'external', 'segger_rtt', 'SEGGER_RTT.c'),
  os.path.join(sdk_path, 'external', 'segger_rtt', 'SEGGER_RTT_Syscalls_GCC.c'),
  os.path.join(sdk_path, 'external', 'segger_rtt', 'SEGGER_RTT_printf.c'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'mdk', 'system_nrf52.c'),]

INC_DIRS = [
  os.path.join('src', 'application', 'bmp280'),
  os.path.join(sdk_path, 'components'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'mdk'),
  os.path.join(sdk_path, 'components', 'libraries', 'scheduler'),
  os.path.join(sdk_path, 'components', 'libraries', 'timer'),
  os.path.join(sdk_path, 'components', 'boards'),
  os.path.join(sdk_path, 'components', 'libraries', 'strerror'),
  os.path.join(sdk_path, 'components', 'toolchain', 'cmsis', 'include'),
  os.path.join(sdk_path, 'components', 'libraries', 'util'),
  os.path.join(sdk_path, 'components', 'libraries', 'balloc'),
  os.path.join(sdk_path, 'components', 'libraries', 'ringbuf'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'hal'),
  os.path.join(sdk_path, 'components', 'libraries', 'bsp'),
  os.path.join(sdk_path, 'components', 'libraries', 'log'),
  os.path.join(sdk_path, 'components', 'libraries', 'button'),
  os.path.join(sdk_path, 'modules', 'nrfx'),
  os.path.join(sdk_path, 'components', 'libraries', 'experimental_section_vars'),
  os.path.join(sdk_path, 'integration', 'nrfx', 'legacy'),
  os.path.join(sdk_path, 'components', 'libraries', 'delay'),
  os.path.join(sdk_path, 'external', 'segger_rtt'),
  os.path.join(sdk_path, 'components', 'libraries', 'atomic_fifo'),
  os.path.join(sdk_path, 'components', 'drivers_nrf', 'nrf_soc_nosd'),
  os.path.join(sdk_path, 'components', 'libraries', 'atomic'),
  os.path.join(sdk_path, 'components', 'libraries', 'sortlist'),
  os.path.join(sdk_path, 'components', 'libraries', 'memobj'),
  os.path.join(sdk_path, 'integration', 'nrfx'),
  os.path.join(sdk_path, 'modules', 'nrfx', 'drivers', 'include'),
  os.path.join(sdk_path, 'external', 'fprintf'),
  os.path.join(sdk_path, 'components', 'libraries', 'log', 'src'),
]

MAKE_VARS = {}
MAKE_INCLUDES = []