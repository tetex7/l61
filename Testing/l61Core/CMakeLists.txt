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
file(GLOB L61_CORE_TEST_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp")
add_executable(l61_core_test ${L61_CORE_TEST_CPP_FILES})

set_target_output(l61_core_test ${BIN_DIR}/testing)

target_link_libraries(
        l61_core_test
        GTest::gtest_main
        l61_core
)

target_link_libraries(l61_core_test base_interface)

include(GoogleTest)
gtest_discover_tests(l61_core_test)