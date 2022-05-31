# C/C++ Template Project
This folder contains a generic project template that can be used for various
C/C++ projects, both local and embedded. Several conventions are used to make
the project easily extendable to multiple boards and target applications; these
are described in more detail below.

# Project Structure
/                       Root directory, contains the master Makefile
/src/                   All custom src files
/build/                 Build directory, contains the build output (if any)
/config/                Configuration files, templates, etc.
/docs/                  Generated docs (if any)
/libs/                  3rd party libraries (e.g. nRF5 SDK)
/scripts/               Helper scripts and automation tools - this includes
                        both generic and custom scripts

# Source Structure
/src/                   Root source directory
/src/common/            Common source files applicaable to all targets
/src/application/       Application specific source files - subfolders should
                        be created for each application
/src/platform/          Platform specific source files (e.g. /src/platform/nrf5dk/board.h)

