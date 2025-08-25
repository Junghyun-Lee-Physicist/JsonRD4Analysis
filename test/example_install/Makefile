.RECIPEPREFIX = >

INSTALL_DIR := ../../install
CXX := g++
CXXFLAGS := -std=c++17 -I$(INSTALL_DIR)/include
LDFLAGS := -L$(INSTALL_DIR)/lib -lJsonRD4Analysis

all: test_json

# Build example using library installed to $(INSTALL_DIR)

test_json: test_json.cpp
>$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -o $@

run: test_json
>LD_LIBRARY_PATH=$(INSTALL_DIR)/lib:$$LD_LIBRARY_PATH ./test_json

clean:
>rm -f test_json

.PHONY: all run clean

