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

file(GLOB L61_CPP_FILES "${CMAKE_SOURCE_DIR}/StandardFrontEnd/src/*.cpp" "${CMAKE_SOURCE_DIR}/StandardFrontEnd/src/**/*.cpp")
add_executable(l61 ${L61_CPP_FILES})

set(CMAKE_SKIP_INSTALL_RULES ON)

set_target_properties(l61 PROPERTIES
        OUTPUT_NAME "l61.out"
        BUILD_RPATH "\$ORIGIN/../lib/native"
)

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(l61 PRIVATE Boost::program_options)

target_link_libraries(l61 PRIVATE l61_core)
target_include_directories(l61 PRIVATE "${CMAKE_SOURCE_DIR}/StandardFrontEnd/include")
target_compile_options(l61 PRIVATE ${L61_TOPLEVEL_COMPILE_ARGS} -std=c++23)
target_compile_definitions(l61 PRIVATE L61_BUILDING)
