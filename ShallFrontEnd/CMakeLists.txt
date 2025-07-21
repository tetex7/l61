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
add_executable(sh61 ${L61_CPP_FILES})

set(CMAKE_SKIP_INSTALL_RULES ON)

set_target_property(sh61 BUILD_RPATH "\$ORIGIN/../lib/native")
set_target_property(sh61 OUTPUT_NAME "sh61.out")

set_target_output(sh61 ${BIN_DIR})

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(sh61 PRIVATE Boost::program_options)

pkg_check_modules(LIB_READLINE readline REQUIRED)
target_link_libraries(sh61 PRIVATE ${LIB_READLINE_LIBRARIES})

target_link_libraries(sh61 PRIVATE l61_core)
target_include_directories(sh61 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(l61 PRIVATE base_interface)
target_compile_definitions(sh61 PRIVATE L61_BUILDING)
