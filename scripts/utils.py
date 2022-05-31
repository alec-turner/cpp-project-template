# -*- coding: utf-8 -*-

"""Helper functions

"""

import os
import subprocess
import importlib
import config


# methods to list available configs
def get_platforms():
  return _get_config_files('platform')

def get_applications():
  return _get_config_files('application')

def get_releases():
  return _get_config_files('release')

def get_targets():
  return _get_config_files('target')

def get_scripts():
  return _get_config_files('scripts')

def _get_config_files(config_type):
  files = os.listdir(os.path.join('config', config_type))
  return [os.path.splitext(f)[0] for f in files if f.endswith('.py') and f != 'template.py']


# methods to load config files
def get_project_config():
  return _load_config('project', None)

def get_target_config(target):
  return _load_config('target', target)

def get_platform_config(platform):
  return _load_config('platform', platform)

def get_application_config(application):
  return _load_config('application', application)

def get_release_config(release):
  return _load_config('release', release)

def get_script_set(name):
  mod = importlib.import_module(f'config.scripts.{name}')
  source = importlib.import_module(getattr(mod, 'MODULE_PATH'))
  method_list = getattr(mod, 'SCRIPTS')
  return {
    method['name']: {
      'args': method['args'],
      'method': getattr(source, method['name'])
    } for method in method_list
  }

def get_build_config(target):
  project_config = get_project_config()
  target_config = get_target_config(target)
  platform_config = get_platform_config(target_config['PLATFORM'])
  application_config = get_application_config(target_config['APPLICATION'])
  release_config = get_release_config(target_config['RELEASE'])

  # merge configs
  build_config = target_config.copy()
  build_config = _merge_config(build_config, platform_config)
  build_config = _merge_config(build_config, application_config)
  build_config = _merge_config(build_config, release_config)
  build_config = _merge_config(build_config, project_config)
  
  return build_config

def _load_config(config_type, config_name):
  if config_name is None:
    mod = importlib.import_module(f'config.{config_type}')
  else:
    mod = importlib.import_module(f'config.{config_type}.{config_name}')

  return { k: getattr(mod, k) for k in dir(mod) if not k.startswith('__') }


def _merge_config(config1, config2):
  config = dict(config1)
  for k,v in config2.items():
    if k in config:
      if type(v) is list:
        config[k] += v
      else:
        raise Exception(f'Conflicting config values for {k}')
    else:
      config[k] = v
  return config


#
def validate_platform(platform):
  if platform not in get_platforms() + ['all']:
    raise ValueError(f'Invalid platform: {platform}')


def validate_application(application):
  if application not in get_applications() + ['all']:
    raise ValueError(f'Invalid application: {application}')


def validate_release(release):
  if release not in get_releases():
    raise ValueError(f'Invalid release: {release}')


def get_build_dir(platform, application, release):
  root_build_dir = config.project.BUILD_DIR
  return os.path.join(root_build_dir, release, platform, application)


def get_toolchain_info(prefix='arm-none-eabi-', test_cmd='gcc'):
  # get path
  out = subprocess.check_output(['which', f'{prefix}{test_cmd}'])
  path = os.path.dirname(out.decode('utf-8').strip())

  # get version
  out = subprocess.check_output([f'{prefix}{test_cmd}', '-dumpversion'])
  version = out.decode('utf-8').strip()

  return {
    'path': path,
    'version': version,
    'prefix': prefix
  }