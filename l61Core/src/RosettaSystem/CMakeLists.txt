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
file(GLOB L61_CORE_ROSETTA_SYSTEM_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB L61_CORE_ROSETTA_SYSTEM_C_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_submodule(l61_core_rosetta_system l61_core SRCS ${L61_CORE_ROSETTA_SYSTEM_CPP_FILES} ${L61_CORE_ROSETTA_SYSTEM_C_FILES})

target_compile_options(l61_core_rosetta_system PRIVATE
        ${L61_CORE_DEBUG_FLAG}
)