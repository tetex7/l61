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
set(CMAKE_SKIP_INSTALL_RULES ON)
file(GLOB L61_CORE_CPP_FILES "${CMAKE_SOURCE_DIR}/l61Core/src/*.cpp")

pkg_check_modules(LIB_LUA lua REQUIRED)

add_library(l61_core_interface INTERFACE)
target_link_libraries(l61_core_interface INTERFACE base_interface)
target_link_libraries(l61_core_interface INTERFACE ${LIB_LUA_LIBRARIES})
target_compile_options(l61_core_interface INTERFACE -fPIC -g)
target_include_directories(l61_core_interface INTERFACE ${CMAKE_SOURCE_DIR}/l61Core/include)
target_compile_definitions(l61_core_interface INTERFACE
        L61_BUILDING_CORE
        $<$<BOOL:${L61_CONFIG_DEBUG}>:L61_DEBUG>
        $<$<NOT:$<BOOL:${L61_CONFIG_DEBUG}>>:L61_RELEASE>
)

add_library(l61_core SHARED ${L61_CORE_CPP_FILES})

function(add_submodule target_name master_module)
    cmake_parse_arguments(ARG "" "" "SRCS" ${ARGN})
    add_library(${target_name} OBJECT ${ARG_SRCS})
    set_target_output(${target_name} ${BIN_DIR}/l61_core_submodule)
    target_link_libraries(${target_name} PUBLIC l61_core_interface)
    target_link_libraries(${master_module} PRIVATE ${target_name})
endfunction()

set(L61_CORE_DEBUG_FLAG $<$<BOOL:${L61_CONFIG_DEBUG}>:-O0> $<$<NOT:$<BOOL:${L61_CONFIG_DEBUG}>>:-O2>)

add_all_subdirectories(${CMAKE_CURRENT_SOURCE_DIR}/src)



set_target_properties(l61_core PROPERTIES
        OUTPUT_NAME "l61Core"
        #LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
)

set_target_output(l61_core ${BIN_DIR})
target_link_libraries(l61_core PUBLIC l61_core_interface)
target_compile_options(l61_core PRIVATE
        ${L61_CORE_DEBUG_FLAG}
)

