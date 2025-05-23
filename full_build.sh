#!/usr/bin/env bash
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

if [[ "$RVER" == "" ]]; then
    RVER="dev"
fi

if [[ "$DEBUG" == "" ]]; then
    DEBUG=1
fi

if [[ "$1" == "clean" ]]; then
    make -C ./extensionRuntime clean
    make clean
    for i in $(ls ./baseExtensions); do
        EX="${i##*.}"
        if [[ "${EX}" != "mk" ]]; then
            make -C ./baseExtensions/${i} clean
        fi
    done
    rm -rfv ./pkg
    rm -rfv ./l61-*-pak
    rm -fv ./l61-*-x86_64.pkg.tar.zst
else
    make -C ./extensionRuntime DEBUG=$DEBUG
    make -j $(nproc) RVER=${RVER} DEBUG=$DEBUG
    for i in $(ls ./baseExtensions); do
        EX="${i##*.}"
        if [[ "${EX}" != "mk" ]]; then
            make -C ./baseExtensions/${i} -j $(nproc) DEBUG=$DEBUG
        fi
    done
fi

