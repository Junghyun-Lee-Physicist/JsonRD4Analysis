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
The library is built and installed using a simple Makefile.

> [!Important]
> The **install directory** must be specified with an absolute path.
> If you prefer not to specify an installation directory, simply create an `install` directory in the base directory. The default installation path is set to that location.

Steps:
  - Move to the `MakefileInstall` directory.
  - At the top of the `Makefile`, set the `INSTALL_ROOT` variable to the absolute path of your desired installation location.
  - To build a shared library, use `CompileShared.sh`; to build a static library, use `CompileStatic.sh`.
```typescript
git clone https://github.com/Junghyun-Lee-Physicist/JsonRD4Analysis.git
cd JsonRD4Analysis/MakefileInstall
# Modify the INSTALL_ROOT variable in the Makefile to the absolute path of your installation directory.

sh CompileShared.sh   // Builds and installs a shared library
```


----------


## Set the environment variables
```typescript
source </path/to/installation>/share/JsonRD4Analysis/JsonRDsetup.sh
// Please replace </path/to/installation> to the absolute path of installation location
```


----------


## How to implement to your source code?
  - The `test` directory now contains Makefile-based examples demonstrating how to link against the library.
  - Review the example code in `test_json.cpp` within each example to understand how to integrate this program into your own project.
```typescript
// Build example code using the library built in MakefileInstall
cd test/example_local
make run

// Build example code using the library installed to ../../install
cd ../example_install
make run
```
