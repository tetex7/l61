# λ61

*A Lua-powered environment for building, scripting, and experimenting.*

**λ61** (aka `l61`) is a hyper-extensible Lua-based environment.  
This is a full rewrite — the original attempt grew into spaghetti with scope creep, so this version is built to be leaner, cleaner, and actually maintainable.

## Purpose

Originally conceived as a build system, λ61 has evolved into a hyper-extensible environment layered on top of [liblua](https://www.lua.org/).  
Think of it as a foundation you can shape into whatever workflow you need, with Lua as the extension language.

## Dependencies

- **Runtime**
    - GCC
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