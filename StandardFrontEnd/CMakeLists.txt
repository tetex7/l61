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

file(GLOB L61_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")
add_executable(l61 ${L61_CPP_FILES})

set(CMAKE_SKIP_INSTALL_RULES ON)

set_target_property(l61 BUILD_RPATH "\$ORIGIN/../lib/native")
set_target_property(l61 OUTPUT_NAME "l61.out")

set_target_output(l61 ${BIN_DIR})

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(l61 PRIVATE Boost::program_options)

target_link_libraries(l61 PRIVATE l61_core)
target_include_directories(l61 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(l61 PRIVATE base_interface)
target_link_libraries(l61 PRIVATE l61_front_end_rt)
target_compile_definitions(l61 PRIVATE L61_BUILDING)
