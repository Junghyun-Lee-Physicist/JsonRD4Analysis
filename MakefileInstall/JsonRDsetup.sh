#!/bin/bash
# setup.sh: Environment variable setup script for both Linux and macOS.
# The INSTALL_ROOT path must match the one used in your Makefile.
#
# This script sets environment variables for:
#   - Build time: CPATH and LIBRARY_PATH
#   - Runtime (dynamic linker): LD_LIBRARY_PATH on Linux, DYLD_LIBRARY_PATH on macOS.

# Obtain the absolute path to the install directory.
# below placeholder will be replaced to absolute path by the Makefile
libAbsPath="%%INSTALL_ROOT%%"

# JsonRD_LIB_ROOT: Base directory where the library and header files are installed.
# This variable is used by projects to locate the installed package.
export JsonRD_LIB_ROOT="${libAbsPath}"

# CPATH: Specifies additional directories for the compiler to search for header files.
# (Used at build time by compilers for C/C++ etc.)
export CPATH="${JsonRD_LIB_ROOT}/include:$CPATH"

# LIBRARY_PATH: Specifies directories for the linker to search for libraries at build time.
# (Used when linking static (.a) or dynamic (.so) libraries; this is a build-time variable.)
export LIBRARY_PATH="${JsonRD_LIB_ROOT}/lib:$LIBRARY_PATH"

# LD_LIBRARY_PATH: On Linux, used at runtime by the dynamic linker to locate shared libraries.
export LD_LIBRARY_PATH="${JsonRD_LIB_ROOT}/lib:$LD_LIBRARY_PATH"

# DYLD_LIBRARY_PATH: On macOS, used at runtime by the dynamic linker to locate shared libraries.
export DYLD_LIBRARY_PATH="${JsonRD_LIB_ROOT}/lib:$DYLD_LIBRARY_PATH"

# Print out the environment variables for verification.
echo "Environment set:"
echo "  JsonRD_LIB_ROOT = $JsonRD_LIB_ROOT"
echo "  CPATH = $CPATH             # Build time header search path"
echo "  LIBRARY_PATH = $LIBRARY_PATH   # Build time library search path (for linking)"
echo "  LD_LIBRARY_PATH = $LD_LIBRARY_PATH   # Runtime shared library search path on Linux"
echo "  DYLD_LIBRARY_PATH = $DYLD_LIBRARY_PATH   # Runtime shared library search path on macOS"
