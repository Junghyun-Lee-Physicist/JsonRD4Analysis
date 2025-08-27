# JsonRD4Analysis
`JsonRD4Analysis` – Json ReaDer for Analysis

JsonRD4Analysis provides a simple and intuitive way to read JSON configurations into C++ projects and expose the values through lightweight singleton interfaces.

The library consists of two core components:

- **JsonConfigReader** – loads JSON files and fills configuration structures.
- **Config interfaces** – header-only singletons that store configuration values and can be included anywhere.

> [!NOTE]
> - Uses `nlohmann/json` as the JSON parser: [nlohmann/json repository](https://github.com/nlohmann/json)
> - Interfaces are implemented as memory–efficient singletons
> - Users may create multiple interface headers to match different JSON layouts

---

## License
This project is licensed under the Apache License 2.0.
It also includes third-party components under different licenses:

- `nlohmann/json` (MIT License) - [https://github.com/nlohmann/json](https://github.com/nlohmann/json)

See `LICENSE` and `NOTICE` files for details.

---

## Installation
All build scripts live in the `installer` directory.  The final installation
prefix defaults to the `install` directory in the project root but can be
changed.

### Option 1 – CMake
```bash
cd installer
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=../install -DBUILD_SHARED_LIBS=ON
cmake --build build
cmake --install build
rm -rf build            # remove intermediates
```

### Option 2 – Makefile
```bash
cd installer
make shared             # or: make static
# artifacts are placed in ../install and build/ is removed
```

Clean everything at any time:
```bash
cd installer
make clean              # removes ../install and build/
```

After installation set up the environment (defaults to `./install` when no path
is given):
```bash
source JsonRDsetup.sh [path/to/install]
```

---

## JSON reader
`JsonConfigReader` reads a configuration file and populates the default
interface `CMSAnalysisConfig` (reachable via the convenience alias
`ConfigInterface`).

Missing mandatory fields cause an error.  Optional fields that are present but
`null` trigger warnings.

To inspect the loaded configuration you can call:
```cpp
JsonConfigReader::getInstance().printJsonConfig();
```
which prints the full JSON structure.

---

## Interfaces
Interfaces live in `include/interfaces`.  The default interface is
`CMSAnalysisConfig.hpp` in namespace `CMSConfig`, which can be accessed through
the umbrella header `ConfigInterface.hpp`:
```cpp
#include "JsonConfigReader.hpp"
#include "ConfigInterface.hpp"   // pulls in interfaces/CMSAnalysisConfig.hpp

int main() {
    auto& reader = JsonConfigReader::getInstance();
    reader.open("config.json");
    auto& cfg = ConfigInterface::getInstance();
    std::cout << "Input path: " << cfg.InputPath << '\n';
    std::cout << "2017 noise filters:" << '\n';
    for (const auto& nf : cfg.noiseFilters["2017noiseFilter"]) {
        std::cout << "  - " << nf << '\n';
    }
    std::cout << "ttTohadronic Xs (2018): "
              << cfg.years.at("2018").samples.at("ttTohadronic").Xs
              << std::endl;
}
```

To create a configuration for a different analysis:
1. Copy `include/interfaces/CMSAnalysisConfig.hpp` to a new header (e.g.
   `DualReadoutConfig.hpp`).
2. Adjust the structs/namespaces to match your JSON layout.
3. Include your new header directly in applications or update
   `include/ConfigInterface.hpp` to alias it instead of `CMSAnalysisConfig.hpp`.

---

## Examples
The `test` directory demonstrates several build/use combinations:

1. `ex1_using_find_package` – library built and used with CMake (`find_package`).
2. `ex2_using_lib_madeby_Makefile` – library built with Makefile and consumed with CMake.
3. `ex3_using_make_only` – library and application both built with Makefile.

Each example contains a `config.json` and minimal code showing how arrays, maps and plain variables are accessed.

---

## JSON structure
A typical configuration might look like:
```json
{
  "FileDescription": "Example json for JsonRD4Analysis",
  "InputPath" : "/user/storage/",
  "OutputPath" : "/user/output/",
  "2016noiseFilter" : ["goodVertices", "HBHENoiseFilter"],
  "2017noiseFilter" : ["goodVertices"],
  "2018noiseFilter" : ["goodVertices"],
  "2018" : {
    "lumi" : 59.7,
    "samples" : {
      "ttTohadronic" : {"Xs":833900, "BR":0.454, "NEvt":232999999, "Wgt":1.0, "Type":"MC"}
    }
  }
}
```
Each year (e.g., `2016PreAPV`, `2016PostAPV`, `2017`, `2018`) contains its own
`lumi` and `samples` map.  Noise filters are provided per year via dedicated
arrays.

---

## Using the installed library
After running the installer and sourcing `JsonRDsetup.sh`, your environment will
contain `JsonRD_LIB_ROOT`, `CPATH`, and `LIBRARY_PATH` variables pointing to the
installed headers and libraries.

### CMake projects
Add the package and link target in your `CMakeLists.txt`:
```cmake
find_package(JsonRD4Analysis REQUIRED)
add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE JsonRD4Analysis::JsonRD4Analysis)
```
`main.cpp` can then include the headers and use the interface:
```cpp
#include "JsonConfigReader.hpp"
#include "ConfigInterface.hpp"

int main() {
    auto& reader = JsonConfigReader::getInstance();
    reader.open("config.json");
    auto& cfg = ConfigInterface::getInstance();
    std::cout << cfg.InputPath << std::endl;
}
```

### Makefile projects
Source `JsonRDsetup.sh` and use the exported variables:
```make
CXX      ?= g++
CXXFLAGS += -I$(JsonRD_LIB_ROOT)/include
LDFLAGS  += -L$(JsonRD_LIB_ROOT)/lib -lJsonRD4Analysis

all: app

app: main.cpp
    $(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
```
The accompanying `main.cpp` is identical to the one shown above.

---
