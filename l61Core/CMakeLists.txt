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

file(GLOB L61_CORE_CPP_FILES "${CMAKE_SOURCE_DIR}/l61Core/src/*.cpp" "${CMAKE_SOURCE_DIR}/l61Core/src/**/*.cpp")
add_library(l61_core SHARED ${L61_CORE_CPP_FILES})

set(CMAKE_SKIP_INSTALL_RULES ON)

set_target_properties(l61_core PROPERTIES
        OUTPUT_NAME "l61Core"
        #LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR}
)

set_target_output(l61_core ${BIN_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIB_LUA lua REQUIRED)

target_link_libraries(l61_core ${LIB_LUA_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR}/l61Core/include)
target_compile_options(l61_core PRIVATE ${L61_TOPLEVEL_COMPILE_ARGS} -fPIC -std=c++23)
target_compile_definitions(l61_core PRIVATE L61_BUILDING_CORE)
