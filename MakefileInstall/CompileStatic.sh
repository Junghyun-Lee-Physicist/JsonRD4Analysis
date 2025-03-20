#!/bin/bash

make clean && make STATIC=1 install
rm -rf libJsonRD4Analysis.a
