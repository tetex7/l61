# λ61

*A Lua-powered environment for building, scripting, and experimenting.*

**λ61** (aka `l61`) is a hyper-extensible Lua-based environment.  
This is a full rewrite — the original attempt grew into spaghetti with scope creep, so this version is built to be leaner, cleaner, and actually maintainable.

## Purpose

Originally conceived as a build system, λ61 has evolved into a hyper-extensible environment layered on top of [liblua](https://www.lua.org/).  
Think of it as a foundation you can shape into whatever workflow you need, with Lua as the extension language.

## Dependencies

- **Runtime**
    - GCC(New enough to compile C++23)
    - Boost.Program_options
    - liblua
    - readline


- **Build**
    - CMake
    - Ninja *or* Make
    - Bash
    - pkgconfig *aka* pkgconf
    - GoogleTest (for testing)


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

## Why λ61?

λ61 isn’t just another Lua wrapper or build system.  
It’s designed to be hyper-extensible, letting you mold it into the workflow you want  
from scripting and building to prototyping complex systems  
all while staying lightweight and maintainable.