# cppug-kl-1122
Code for the C++ User Group Kaiserslautern from November 2022.

## CMake Documentation and References

For additional information on CMake, have a look at the following references:
- [CMake's official documentation](https://cmake.org/documentation/)
- [Modern CMake for C++](https://www.packtpub.com/product/modern-cmake-for-c/9781801070058) (also available on other online shops)
- Several YouTube talks:
  - [CppCon 2017: Mathieu Ropert "Using Modern CMake Patterns to Enforce a Good Modular Design"](https://youtu.be/eC9-iRN2b04)
  - [C++Now 2017: Daniel Pfeifer "Effective CMake"](https://youtu.be/bsXLMQ6WgIk)
  - [CppCon 2018: Mateusz Pusz "Git, CMake, Conan - How to ship and reuse our C++ projects"](https://youtu.be/S4QSKLXdTtA)
  - [CppCon 2019: Craig Scott "Deep CMake for Library Authors"](https://youtu.be/m0DwB4OvDXk)
  - [Meeting C++ 2019: Deniz Bahadir "Oh No! More Modern CMake"](https://youtu.be/y9kSr5enrSk) (DANGER: See notes below)
  - [Microsoft Developer: An Introduction to CMakePresets.json](https://youtu.be/NFbnm1t6Mc4)
  - [CppCon 2021: Bret Brown "Modern CMake Modules"](https://youtu.be/IZXNsim9TWI)
  - [CppCon 2022: Bill Hoffman "import CMake, CMake and C++20 Modules"](https://youtu.be/5X803cXe02Y)
  - [C++Now 2022: Bill Hoffman "Modules and More"](https://youtu.be/hkefPcWySzI)

> ---
> **NOTES:**
>
> - Don't override builtin CMake commands/functions.
>   This is very error prone and generally considered bad practice.
> - Don't use `CMAKE_PROJECT_INCLUDE[_BEFORE]` as described in the video.
>   This CMake functionality is meant for injection not what it is used for in the talk.
>
> ---

## Using CMake Graphical User Interface

> ---
> **PROJECT CONFIGURATION ONLY**
>
> ---

CMake comes with 2 graphical tools for configuring projects:
- `ccmake` is terminal based using ncurses.
- `cmake-gui` is based on the OS's window system using Qt.

These tools are extremely useful for exploring unknown project options and settings.
The commands listed below for configuring a project are useable by both tools.

## Using CMake Command-Line Interface

### Configuring a project

**Pre-Modern:**
```
cd <build-dir>
cmake –D CMAKE_TOOLCHAIN_FILE=toolchain.cmake
      –D CMAKE_INSTALL_PREFIX=install
      –D CMAKE_INSTALL_MESSAGE=LAZY
      <path-to-source-dir>
```

**Modern:**
```
cmake –C build-config.cmake
      --toolchain toolchain.cmake
      -B <build-dir>
      -S <source-dir>
```
- `-C` is supported since CMake 3.0.
- `--toolchain` is supported since CMake 3.21.
  On older versions the toolchain file is set via `-D CMAKE_TOOLCHAIN_FILE=<toolchain-file>`.

**Post-Modern:**
```
cmake --preset <preset-name>
      -S <source-dir>
```
Presets are supported since CMake 3.19.

### Building a configured project

**Pre-Modern:**
```
cd <build-dir>
make –j 8
```

**Modern:**
```
cmake --build build -j 8
```
- `--build` is supported since CMake 3.0.
- `-j\|--parallel` is supported since CMake 3.12.
  In previous version the option can be added by passing additional compiler arguments: `-- -j 8`.

**Post-Modern:**
```
cd <source-dir>
cmake --build –-preset <preset-name>
```
Build presets are supported since CMake 3.20.

### Testing a built project

**Pre-Modern:**
```
cd <build-dir>
ctest --output-on-failure
```

**Modern:**
```
ctest --test-dir <build-dir> --output-on-failure
```
```
cd <source-dir>
ctest --preset <preset-name>
```
`--test-dir` and `--preset` are supported since CMake 3.20.

### Installing a built project

**Pre-Modern:**
```
cd <build-dir>
make install
```

**Modern:**
```
cmake --install <build-dir>
```
`--install` is supported since CMake 3.15.

**Wishful Thinking:**
```
cd <source-dir>
cmake --install --preset <preset-name>
```
