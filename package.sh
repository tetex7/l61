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

min=0
max=99999
ra=$((min + RANDOM % $((max-min))))

PAK_NAME="l61-${ra}-pak"

cp -rv ./deploymentFileSystem ./${PAK_NAME}
cp -v ./build/l61.out ./${PAK_NAME}/bin/l61
mkdir -p "${PAK_NAME}/lib/native"

for i in $(ls ./baseExtensions); do
        EX="${i##*.}"
        if [[ "${EX}" != "mk" ]]; then
            cp -v "./baseExtensions/${i}/${i}.lex61" "./${PAK_NAME}/lib/native"
        fi
done

cp -rv ./include ./${PAK_NAME}/l61_include
cp -v ./extensionRuntime/l61_extension_rt.o "./${PAK_NAME}/lib/native"
cp -v ./extensionRuntime/lex61rt.hpp ./${PAK_NAME}/l61_include/lex61rt.hpp