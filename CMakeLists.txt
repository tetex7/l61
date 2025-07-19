#
# Copyright (C) 2025  tetex7
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

cmake_minimum_required(VERSION 3.24.0)
project(lambda61 LANGUAGES CXX C)

set(CMAKE_SKIP_INSTALL_RULES ON)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

# Optional: turn this off for faster dev builds
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(BuildOptions.cmake)

set(EXECUTABLE_OUTPUT_PATH "${BIN_DIR}")
set(LIBRARY_OUTPUT_PATH  "${BIN_DIR}")

configure_file(
        ${CMAKE_SOURCE_DIR}/l61_config.h.in
        ${CMAKE_SOURCE_DIR}/l61Core/include/l61/l61_config.h
)

# Include top-level headers
include_directories(${CMAKE_SOURCE_DIR}/l61Core/include)
include_directories(${CMAKE_SOURCE_DIR}/extensionRuntime)

# Add subdirectories
add_subdirectory(l61Core)
add_subdirectory(extensionRuntime)
add_subdirectory(StandardFrontEnd)

# Add extensions last (can be dynamic later)
add_subdirectory(baseExtensions)