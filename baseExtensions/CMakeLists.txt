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

function(add_l61_lex61_target target_name output_filename object_files)
    add_library(${target_name} SHARED ${object_files})

    set_target_properties(${target_name} PROPERTIES
            OUTPUT_NAME "${output_filename}"
            PREFIX ""
            SUFFIX ".lex61"
    )
    set_target_output(${target_name} ${BIN_DIR})
    target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${target_name} PRIVATE l61_rt)
    target_link_libraries(${target_name} PRIVATE l61_core)
    target_compile_options(${target_name} PRIVATE ${L61_TOPLEVEL_COMPILE_ARGS} -fPIC -std=c++23)
endfunction()

function(add_all_subdirectories BASE_DIR)
    file(GLOB CHILD_DIRS RELATIVE ${BASE_DIR} "${BASE_DIR}/*")

    foreach(child ${CHILD_DIRS})
        set(full_path "${BASE_DIR}/${child}")
        if(IS_DIRECTORY ${full_path})
            if(EXISTS "${full_path}/CMakeLists.txt")
                add_subdirectory(${full_path})
            endif()
        endif()
    endforeach()
endfunction()

add_all_subdirectories(${CMAKE_CURRENT_SOURCE_DIR})