# Istd
 A library that extends the C standard library.

# How to build

## Build Test

premake5 is required to build the test.

use the build/*.bat files to compile to your compiler if on windows.

If not use `premake5 [target] -cc=[compiler]`

## Build Istd

Istd currently only supports C17 older versions may work but they are not tested or officially supported for now. 
Istd is also mainly designed for x86_64 platforms. x86 may work but is not test or officially supported.

Istd currently requires two defines `NDEBUG` which is defined when in release mode and `DEBUG` which is defined when in debug mode. 

# Documentation 

All functions and structs should be documented in header files.
