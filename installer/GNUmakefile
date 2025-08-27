## installer/GNUmakefile - build JsonRD4Analysis using plain Make

INSTALL_ROOT ?= $(CURDIR)/../install
BUILD_DIR := $(CURDIR)/build

CXX := g++
CXXFLAGS := -std=c++17 -Wall -I../include -fPIC

SRCS := ../src/JsonConfigReader.cpp
OBJS := $(BUILD_DIR)/JsonConfigReader.o

LIB_SHARED := $(INSTALL_ROOT)/lib/libJsonRD4Analysis.so
LIB_STATIC := $(INSTALL_ROOT)/lib/libJsonRD4Analysis.a

.PHONY: all shared static clean

all: shared

shared: $(LIB_SHARED)

static: $(LIB_STATIC)

$(BUILD_DIR)/%.o: ../src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_SHARED): $(OBJS)
	@mkdir -p $(INSTALL_ROOT)/lib
	$(CXX) -shared -o $@ $^
	@mkdir -p $(INSTALL_ROOT)/include
	cp -r ../include/* $(INSTALL_ROOT)/include/
	@rm -rf $(BUILD_DIR)

$(LIB_STATIC): $(OBJS)
	@mkdir -p $(INSTALL_ROOT)/lib
	ar rcs $@ $^
	@mkdir -p $(INSTALL_ROOT)/include
	cp -r ../include/* $(INSTALL_ROOT)/include/
	@rm -rf $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(INSTALL_ROOT)
