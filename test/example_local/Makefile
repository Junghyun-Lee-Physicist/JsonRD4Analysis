.RECIPEPREFIX = >

CXX := g++
CXXFLAGS := -std=c++17 -I../../include
LDFLAGS := -L../../MakefileInstall -lJsonRD4Analysis

all: test_json

# Build example using library built but not installed
# Assumes libJsonRD4Analysis is present in ../../MakefileInstall

test_json: test_json.cpp
>$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@

run: test_json
>LD_LIBRARY_PATH=../../MakefileInstall:$$LD_LIBRARY_PATH ./test_json

clean:
>rm -f test_json

.PHONY: all run clean

