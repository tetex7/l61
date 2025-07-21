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

file(GLOB L61_RT_CPP_FILES "${CMAKE_SOURCE_DIR}/extensionRuntime/rt_main.cpp")
add_library(l61_rt STATIC ${L61_RT_CPP_FILES})

set(CMAKE_SKIP_INSTALL_RULES ON)

set_target_properties(l61_rt PROPERTIES
        OUTPUT_NAME "l61_lex61_rt"
        #LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
)

set_target_output(l61_rt ${BIN_DIR})

target_include_directories(l61_rt PUBLIC ${CMAKE_SOURCE_DIR}/extensionRuntime)
target_link_libraries(l61_rt PUBLIC l61_core)
target_link_libraries(l61_rt PRIVATE base_interface)
target_compile_options(l61_rt PRIVATE -fPIC)
target_compile_definitions(l61_rt PRIVATE L61_RT_BUILDING)
