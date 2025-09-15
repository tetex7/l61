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

function(add_l61_lex61_target target_name output_filename)
    cmake_parse_arguments(ARG "" "" "SRCS" ${ARGN})
    add_library(${target_name} SHARED ${ARG_SRCS})

    set_target_properties(${target_name} PROPERTIES
            OUTPUT_NAME "${output_filename}"
            PREFIX ""
            SUFFIX ".lex61"
    )
    set_target_output(${target_name} ${BIN_DIR})
    set_target_property(${target_name} BUILD_RPATH "\$ORIGIN")
    target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${target_name} PRIVATE l61_lex61_rt)
    target_link_libraries(${target_name} PRIVATE l61_core)
    target_link_libraries(${target_name} PRIVATE base_interface)
    target_compile_options(${target_name} PRIVATE -fPIC -g)
    #set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endfunction()

add_all_subdirectories(${CMAKE_CURRENT_SOURCE_DIR})