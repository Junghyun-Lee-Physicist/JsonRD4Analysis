# INSTALL_ROOT: Root directory for installing libraries and headers.
# Default is set to the "install" directory at the project root (relative path).
INSTALL_ROOT ?= $(CURDIR)/../install

# TMP_DIR: Directory to store object files.
# Default: "tmp" directory at the project root.
TMP_DIR ?= $(CURDIR)/tmp

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I../include -fPIC

# Source files and target library names
SRCS := ../src/JsonConfigReader.cpp
# patsubst function: converts each .cpp file in $(SRCS) (with pattern ../src/%.cpp)
# into an object file in $(TMP_DIR) with a .o extension (i.e., $(TMP_DIR)/%.o)
OBJS := $(patsubst ../src/%.cpp,$(TMP_DIR)/%.o,$(SRCS))
LIB_STATIC := libJsonRD4Analysis.a   # Static library name
LIB_SHARED := libJsonRD4Analysis.so   # Shared library name

# Build type selection:
# Use STATIC=1 for static library or SHARED=1 for shared library.
# Default (if neither is defined) is to build a shared library.
ifeq ($(STATIC),1)
    TARGET := $(LIB_STATIC)
    LDFLAGS :=
    LINK_CMD := ar rcs $(TARGET) $(OBJS)
else ifeq ($(SHARED),1)
    TARGET := $(LIB_SHARED)
    LDFLAGS := -shared
    LINK_CMD := $(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)
else
    # Default: build shared library
    TARGET := $(LIB_SHARED)
    LDFLAGS := -shared
    LINK_CMD := $(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)
endif

.PHONY: all clean install

# 'all' target: Builds the selected library (static or shared)
#    --> all : Final target of build
all: $(TARGET)

#####################################################################################
# Compiling Part : Making object for each source code and link them together. EASY :)

# Pattern rule: Compile .cpp files from ../src into .o files in TMP_DIR.
$(TMP_DIR)/%.o: ../src/%.cpp
	@mkdir -p $(TMP_DIR)         # Ensure TMP_DIR exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into the final library (static or shared)
$(TARGET): $(OBJS)
	$(LINK_CMD)

#####################################################################################

# 'clean' target: Remove object files and library files.
clean:
	rm -f $(OBJS) $(LIB_STATIC) $(LIB_SHARED)

# 'install' target: Install the library and header files to INSTALL_ROOT.
install: $(TARGET)
	@echo "Installing to $(INSTALL_ROOT)"
	# Create lib directory and copy the library file.
	mkdir -p $(INSTALL_ROOT)/lib
	cp $(TARGET) $(INSTALL_ROOT)/lib/
	# Create include directory and copy the entire include folder.
	mkdir -p $(INSTALL_ROOT)/include
	cp -r ../include $(INSTALL_ROOT)/
	# Copy environment script
	mkdir -p $(INSTALL_ROOT)/share/JsonRD4Analysis
	cp -r JsonRDsetup.sh $(INSTALL_ROOT)/share/JsonRD4Analysis/
	sed 's|%%INSTALL_ROOT%%|$(realpath $(INSTALL_ROOT))|g' JsonRDsetup.sh > $(INSTALL_ROOT)/share/JsonRD4Analysis/JsonRDsetup.sh
