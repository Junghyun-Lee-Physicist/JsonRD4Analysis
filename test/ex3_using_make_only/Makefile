CXX := g++
CXXFLAGS := -std=c++17 -I$(JsonRD_LIB_ROOT)/include
LDFLAGS := -L$(JsonRD_LIB_ROOT)/lib -lJsonRD4Analysis

all: test_json

test_json: test_json.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f test_json
