# λ61

*A Lua-powered environment for building, scripting, and experimenting.*

**λ61** (aka `l61`) is a hyper-extensible Lua-based environment.  
This is a full rewrite — the original attempt grew into spaghetti with scope creep, so this version is built to be leaner, cleaner, and actually maintainable.

## Purpose

Originally conceived as a build system, λ61 has evolved into a hyper-extensible environment layered on top of [liblua](https://www.lua.org/).  
Think of it as a foundation you can shape into whatever workflow you need, with Lua as the extension language.

## Dependencies

- **Runtime**
    - [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/) (New enough to compile C++23)
    - [Boost.Program_options](https://boost.org) (For The Standard Front End)
    - [Google's Abseil](https://github.com/abseil/abseil-cpp)
    - [liblua](https://lua.org)
    - readline


- **Build**
    - CMake
    - Ninja *or* Make
    - Bash
    - pkgconfig *aka* pkgconf
    - [GoogleTest](https://github.com/google/googletest) (for testing)


- **Bundled Libraries**
  - [sol2](https://github.com/ThePhD/sol2)
  - [nlohmann's json](https://github.com/nlohmann/json)

## Status

Work in progress — expect breaking changes, missing features, and rough edges. Contributions, ideas, and experiments are welcome.

## Getting Started
```bash
git clone https://github.com/tetex7/l61.git # Clone the project to your local machine
cd ./l61 # Changes your current working directory to the project

./dev_setup.sh # Initializes the Cmake environment
./dev_setup.sh mk # Builds the project
./package.sh # Packages the project into a portable usable File structure

./l61-deployment-package/bin/l61 --help
```
### FreeBSD is a little different
And since freeBSD packages Lua with its version name I use `-DL61_CONFIG_LUA_PACKAGE_NAME="lua-X.X"`   
One small note clang is used on FreeBSD  
```bash
git clone https://github.com/tetex7/l61.git # Clone the project to your local machine
cd ./l61 # Changes your current working directory to the project

./dev_setup.sh -DL61_CONFIG_LUA_PACKAGE_NAME="lua-5.4"
./dev_setup.sh mk 

./package.sh # Packages the project into a portable usable File structure

./l61-deployment-package/bin/l61 --help
```
I have not tested it on OpenBSD yet 
# Why λ61?

λ61 isn’t just another Lua wrapper or a Runtime.  
It’s designed to be hyper-extensible, letting you mold it into the workflow you want  
from scripting and building to prototyping complex systems  
all while staying lightweight and maintainable.
