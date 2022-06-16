# C/C++ Template Project
This folder contains a generic project template that can be used for various
C/C++ projects, both local and embedded. Several conventions are used to make
the project easily extendable to multiple boards and target applications; these
are described in more detail below.

# Project Structure
/                       Root directory, contains the master Makefile
/src/                   All custom src files
/build/                 Build directory, contains the build output (if any)
/config/                Configuration files
/docs/                  Generated doxygen docs (if any)
/libs/                  3rd party libraries (e.g. nRF5 SDK)
/res/                   Additional resources (e.g. makefile templates, linker
                        scripts, etc.)
/scripts/               Helper scripts and automation tools - this includes
                        both generic and custom scripts

# Source Structure
/src/                   Root source directory
/src/common/            Common source files applicaable to all targets
/src/application/       Application specific source files - subfolders should
                        be created for each application
/src/platform/          Platform specific source files (e.g.
                        /src/platform/nrf5dk/board.h)

# Adding New Configurations

## General Notes

  * As config files are written with python, variables can be assigned
    dynamically. See scripts/utils for more details on how these config files
    are loaded.
  
  * Variables must be upper case; lower or mixed case variables will be ignored
    when reading config files. This allows local variables to be defined
    without affecting other config files.

## Adding a New Target

  1. To add a new target, start by making a new copy of
     config/targets/template.mk

  2. Name the new file something brief and descriptive, then fill in the
     contents as required
  
  3. If additional resources are required, these should be added in the res/
     directory.

## Adding a New Application

  1. To add a new application, start by making a new copy of
     config/applications/template.mk

  2. Name the new file something brief and descriptive, then fill in the
     contents as required

  3. By convention, a new subfolder should be made in the src/application
     directory for the new application. This folder should contain the
     application specific source files.

## Adding a New Platform

  1. To add a new platform, start by making a new copy of
     config/platforms/template.mk

  2. Name the new file something brief and descriptive, then fill in the
     contents as required
  
## Adding a New Release

  1. To add a new release, start by making a new copy of
     config/releases/template.mk

  2. Name the new file something brief and descriptive, then fill in the
     contents as required


# Example Configurations

  ## Platforms

      * pca10040: PCA10040 (nRF5 DK) board.

      * local: Local development platform (e.g. 64-bit Linux).

  ## Releases

      * debug: "-Og -g" compile flags.

      * production: "-O3" compile flags.

  ## Applications

      * hello_world: A simple hello world example intended to be run locally.

      * unittest: An example unittest application intended to be run locally.

      * blinky: The basic "blinky" example based on the nRF5 SDK example of the
                same name; intended to be run on the pca10040 platform.

      * bmp280: An example application for monitoring the temperature and
                pressure from a BMP280 sensor. Can be used with either SPI or
                TWI (I2C) interface by building with "-DBMP280_INTERFACE=xxx"
                ("SPI" or "TWI").

   ## Targets

      * hello:
         - application: hello_world
         - platform: pca10040
         - release: debug
      
      * unittest:
         - application: unittest
         - platform: local
         - release: debug

      * blinky:
         - application: blinky
         - platform: pca10040
         - release: debug

      * blinky_production:
         - application: blinky
         - platform: pca10040
         - release: production

      * bmp280_spi:
         - application: bmp280
         - platform: pca10040
         - release: debug

      * bmp280_twi:
         - application: bmp280
         - platform: pca10040
         - release: debug

      