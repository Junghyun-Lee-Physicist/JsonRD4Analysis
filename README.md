# JsonRD4Analysis
`JsonRD4Analysis` – Json ReaDer for Analysis

JsonRD4Analysis provides a simple and intuitive way to read JSON configurations into C++ projects.

The code is organized into two main class types: `JsonReader` and `interface`.
After loading your configuration via `JsonReader` using the `nlohmann/json` parser, configuration values become instantly accessible throughout your code by including the corresponding `interface`.

> [!NOTE]
> - Uses `nlohmann/json` as the JSON parser: [nlohmann/json repository](https://github.com/nlohmann/json)
> - Implements a memory-efficient singleton pattern for the `interface` class
> - Easily customizable through inheritance from the `JsonReader` class, allowing you to adapt the reader to your specific need


----------


## License
This project is licensed under the Apache License 2.0.
It also includes third-party components under different licenses:

- `nlohmann/json` (MIT License) - [https://github.com/nlohmann/json](https://github.com/nlohmann/json)

See `LICENSE` and `NOTICE` files for details.


----------


## Installation
Installation can be done in two ways:
    - Using CMake
    - Using Makefile
> [!Important]
> Regardless of the installation method you choose, the **install directory** must be specified with an absolute path.
> If you prefer not to specify an installation directory, simply create an install directory in the base directory. The default installation path is set to that location.

Option1) Installation using CMake
  - Use the `-DCMAKE_INSTALL_PREFIX` option with an absolute path to specify your desired installation directory.
  - If you want to build a shared library, set the `-DBUILD_SHARED_LIBS` option to `ON`; if you prefer a static library, set it to `OFF`.
```typescript
mkdir build && cd build

cmake .. -DCMAKE_INSTALL_PREFIX="</path/to/installation>" -DBUILD_SHARED_LIBS=ON // In this case, a shared library will be built.
// Please set </path/to/installation> to the absolute path of your desired installation location

make && make install
```

Option2) Installation using Makefile
  - Move to the `MakefileInstall` directory.
  - At the top of the `Makefile`, there is an `INSTALL_ROOT` variable. Assign the absolute path of your desired installation location to this variable.
  - To build a shared library, use `CompileShared.sh`; to build a static library, use `CompileStatic.sh`.
```typescript
cd MakefileInstall
// Modify the INSTALL_ROOT variable in the Makefile to the absolute path of your installation directory.

sh CompileShared.sh // In this case, a shared library will be built.
```


----------


## Set the environment variables
```typescript
source </path/to/installation>/share/JsonRD4Analysis/JsonRDsetup.sh
// Please replace </path/to/installation> to the absolute path of installation location
```


----------


## How to implement to your source code?
  - In the `test` directory, example `CMakeLists` are provided demonstrating how to configure your project for both CMake-based and Makefile-based builds.
  - By reviewing the example code in `test_json.cpp`, you can easily understand how to integrate this program into your own project.
```typescript
// How to build example code
// In the example directory,
mkdir build && cd build
cmake ..
make
./test_json
```
