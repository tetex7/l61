#
# Copyright (C) 2025  Tetex7
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

#set -e

readonly PAK_NAME="l61-deployment-package"

rm -rf ./${PAK_NAME}

cp -rv ./deploymentFileSystem ./${PAK_NAME}
cp -v ./build/l61.out ./${PAK_NAME}/bin/l61
cp -v ./build/sh61.out ./${PAK_NAME}/bin/sh61
mkdir -p "${PAK_NAME}/lib/native"

find ./build -maxdepth 1 -type f -name "*.lex61" -exec cp -v {} "./${PAK_NAME}/lib/native" \;

cp -v ./build/libl61Core.so "./${PAK_NAME}/lib/native/libl61Core.so"
cp -rv ./l61Core/include ./${PAK_NAME}/l61_include
cp -v ./build/libl61_lex61_rt.a "./${PAK_NAME}/lib/native"
cp -v ./extensionRuntime/lex61rt.hpp ./${PAK_NAME}/l61_include/lex61rt.hpp

find "./${PAK_NAME}" -maxdepth 10 -type f -name ".holdOpen.txt" -exec rm -vf {} \;

GIT_COMMIT_HASH=$(git rev-parse --short HEAD)

echo "Built: $(date)" > "${PAK_NAME}/build-info.txt"
echo "Commit: ${GIT_COMMIT_HASH}" >> "${PAK_NAME}/build-info.txt"