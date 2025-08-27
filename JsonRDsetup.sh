#!/bin/bash
# JsonRD4Analysis environment setup script
# Usage: source JsonRDsetup.sh [install_prefix]
# If no prefix is given, use the 'install' directory relative to this script.

if [ -n "$1" ]; then
  libAbsPath="$1"
else
  script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  libAbsPath="${script_dir}/install"
fi

export JsonRD_LIB_ROOT="${libAbsPath}"
export CPATH="${JsonRD_LIB_ROOT}/include:${CPATH}"
export LIBRARY_PATH="${JsonRD_LIB_ROOT}/lib:${LIBRARY_PATH}"
export LD_LIBRARY_PATH="${JsonRD_LIB_ROOT}/lib:${LD_LIBRARY_PATH}"
export DYLD_LIBRARY_PATH="${JsonRD_LIB_ROOT}/lib:${DYLD_LIBRARY_PATH}"
export JsonRD4Analysis_DIR="${JsonRD_LIB_ROOT}/share/JsonRD4Analysis/cmake"

echo "Environment set for JsonRD4Analysis"
echo "  JsonRD_LIB_ROOT = ${JsonRD_LIB_ROOT}"
echo "  CPATH = ${CPATH}"
echo "  LIBRARY_PATH = ${LIBRARY_PATH}"
echo "  LD_LIBRARY_PATH = ${LD_LIBRARY_PATH}"
echo "  DYLD_LIBRARY_PATH = ${DYLD_LIBRARY_PATH}"
echo "  JsonRD4Analysis_DIR = ${JsonRD4Analysis_DIR}"
