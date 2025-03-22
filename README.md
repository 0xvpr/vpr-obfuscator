<h1 align="center">vpr-obfuscator</h1>
<div class="badges" align="center">
  <img src="https://img.shields.io/badge/Version-1%2E0%2E0-44CC11"/>
  <img src="https://img.shields.io/badge/GCC-supported-44CC11"/>
  <img src="https://img.shields.io/badge/Clang-supported-44CC11"/>
  <img src="https://img.shields.io/badge/MinGW-supported-44CC11"/>
  <a href="https://mit-license.org/"><img src="https://img.shields.io/badge/License-MIT-44CC11"/></a>
  <a href="https://github.com/0xvpr/vpr-obfuscator/actions/workflows/ci.yml"><img src="https://github.com/0xvpr/vpr-obfuscator/actions/workflows/ci.yml/badge.svg?branch=main"></a>
</div>

<div class="sub-title">
  <h3 align="center">A cross-platform, single-header-only compile-time obfuscation library.</h3>
</div>

### Demonstration
```bash
( cd example && make )
g++ -std=c++20 -Ofast -I../include -Wall -Wextra -Werror -Wpedantic -Wconversion -Wshadow -Woverflow main.cpp -s -o example.exe
./example.exe
Obfuscated text: A-very-obvious-string-that-would-be-noticable
strings example.exe | egrep -i 'very|obvious|string|that|would|be|noticable' # code 1 == nothing found
make: *** [makefile:9: all] Error 1
```

### Features
- Provides compile-time obfuscated data at all\*\* optimization levels. (\*\*tested on clang/gcc/MSVC)
- Supports **Symmetric** and **Asymmetric** obfuscation implementations.
- Extremely light-weight and portable.
- Highly modular and customizable.

### Integration
- curl
  ```bash
  curl -LSsO obf.hpp 'https://raw.githubusercontent.com/0xvpr/vpr-obfuscator/refs/heads/main/include/vpr/obf.hpp'
  ```
- cmake  
  Terminal
  ```bash
  cmake -B build
  cmake --install build --prefix=<path/to/prefix> # install as /path/to/prefix/include/vpr/obf.hpp
  # cmake --install build # for a global installation
  ```
  CMakeLists.txt
  ```cmake
  find_package(vpr-obfuscator REQUIRED)
  
  add_executable(my_app main.cpp)
  target_link_libraries(my_app PRIVATE vpr::vpr-obfuscator)
  ```
