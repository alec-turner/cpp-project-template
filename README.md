# nRF Template Project
This folder contains a generic project template that can be used for various
nRF-based projects. Several conventions are used to make the project easily
extendable to multiple boards and target applications; these are described in
more detail below.

# Project Structure
/                        Root directory, contains the master Makefile
/src/                    All custom src files
/build/                  Build directory, contains the build output
/docs/                   Generated docs (if any)
/makefiles/              Template makefiles used to build the project
/libs/                   3rd party libraries
/scripts/                Helper scripts and automation tools

# Source Structure
/src/                    Root source directory
/src/common/             Common source files applicaable to all targets
/src/app/                Application specific source files
/src/platform/           Platform specific source files (e.g. /src/platform/nrf5dk/board.h)

