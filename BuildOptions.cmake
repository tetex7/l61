#
# Copyright (C) 2024  Tetex7
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
include_guard(GLOBAL)
execute_process(
        COMMAND ${CMAKE_C_COMPILER} -dumpmachine
        OUTPUT_VARIABLE PLATFORM_TRIPLE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/build)



set(L61_TOPLEVEL_CPP_COMPILE_ARGS -Wall -Wextra -Werror -Wpedantic -fno-strict-aliasing -DSOL_ALL_SAFETIES_ON -include ${CMAKE_SOURCE_DIR}/l61Core/include/l61/PseudoKeywords.hpp)

set(L61_TOPLEVEL_C_COMPILE_ARGS -Wall -Wextra -Werror -fno-strict-aliasing)

set(CMAKE_OBJCOPY "${PLATFORM_TRIPLE}-objcopy" CACHE STRING "Compiler's object copy")

if(NOT WIN32)
    option(L61_CONFIG_STATIC_ONLY "If to produce a static only library" OFF)
else ()
    option(L61_CONFIG_STATIC_ONLY "If to produce a static only library" ON)
endif ()

# Debug flag control
option(L61_CONFIG_DEBUG "Enable debug mode" OFF)

if(L61_CONFIG_DEBUG)
    message(STATUS "L61 Debug mode enabled")
endif()


option(L61_CONFIG_USE_LIB_SAFENET "" OFF)

option(L61_CONFIG_THREAD_AWARE "Determine if the program should be built with thread awareness" ON)

set(L61_CONFIG_STR_VERSION "0.0.0" CACHE STRING "Set the version being compiled")
set(L61_CONFIG_VERSION_MAJOR 0 CACHE STRING "Set the major version being compiled")
set(L61_CONFIG_VERSION_MINOR 0 CACHE STRING "Set the minor version being compiled")
set(L61_CONFIG_VERSION_PATCH 0 CACHE STRING "Set the patch version being compiled")

string(TIMESTAMP L61_CONFIG_GENERATION_DATE "%m-%d-%Y(%H:%M:%S)")
string(TIMESTAMP L61_CONFIG_GENERATION_YEAR "%Y")

execute_process(COMMAND git rev-parse --short HEAD OUTPUT_VARIABLE GIT_COMMIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)
