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
project(lambda61 LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)
enable_testing()

include(BuildOptions.cmake)
include(base_interface.cmake)

set(CMAKE_SKIP_INSTALL_RULES ON)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

# Optional: turn this off for faster dev builds
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(load_component component)
    if(IS_DIRECTORY "${component}" )
        if(EXISTS "${component}/CMakeLists.txt")
            message(STATUS "Loaded Component: ${component}")
            add_subdirectory("${component}")
            return()
        endif ()
    endif ()
    message(FATAL_ERROR "Component Not Found: ${component}")
endfunction()

function(add_all_subdirectories BASE_DIR)
    file(GLOB CHILD_DIRS RELATIVE ${BASE_DIR} "${BASE_DIR}/*")

    foreach(child ${CHILD_DIRS})
        set(full_path "${BASE_DIR}/${child}")
        if(IS_DIRECTORY ${full_path})
            if(EXISTS "${full_path}/CMakeLists.txt")
                load_component(${full_path})
            endif()
        endif()
    endforeach()
endfunction()

function(set_target_property target_name key value)
    set_target_properties(${target_name} PROPERTIES
            ${key} ${value}
    )
endfunction()

function(set_target_output target_name out_path)
    set_target_properties(${target_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${out_path}"
            LIBRARY_OUTPUT_DIRECTORY "${out_path}"
            ARCHIVE_OUTPUT_DIRECTORY "${out_path}"
    )
endfunction()



configure_file(
        ${CMAKE_SOURCE_DIR}/l61_config.h.in
        ${CMAKE_SOURCE_DIR}/l61Core/include/l61/l61_config.h
)

# Add subdirectories
load_component(l61Core)
load_component(frontendRuntime)
load_component(extensionRuntime)
load_component(StandardFrontEnd)
#load_component(ShallFrontEnd)

# Add extensions last (can be dynamic later)
load_component(baseExtensions)
load_component(Testing)