#!/bin/env bash
#
# Copyright (C) 2025 Tetex7
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
set -e
#set -u
set -o pipefail

[[ "$TRS_DEV_SETUP_VERBOSE" == "1" ]] && set -x

#if [[ -z "${CMAKE_GEN}" ]]; then
#    CMAKE_GEN="Ninja"
#fi

function help() {
    echo -e "Dev Setup Script"
    echo "Usage: $0 [clean|(rebuild|rb)|(help|h)|make|<cmake-args>]"
    echo
    echo "  [--]clean              Cleans the cmake environment"
    echo "  [--]rebuild | [-]rb    Clean and reconfigure the cmake environment"
    echo "  [--]help    | [-]h     Show this help message"
    echo "  [--]make    | [-]mk    Run the build with detected system"
    echo "  [--]package | [-]pkg   Makes a package using makepkg(Arch)"
    echo "  [--]build   | [-]b     Build the cmake environment"
    echo "  <cmake args>           Pass-through arguments to cmake"
    echo
    echo "\$CMAKE_GEN = 'Ninja' | 'Unix Makefiles'"
    exit 0
}

function rebuild()
{
    "$0" clean
    "$0" "$@"
    exit $?
}

function build()
{
    #CC=/usr/bin/gcc
    #Ninja
    cmake -G "$CMAKE_GEN" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DL61_CONFIG_DEBUG=ON $@  .
}

function clean()
{
    if [[ -f "./Makefile" ]]; then
        make clean
        rm -fv ./Makefile
    elif [[ -f "./build.ninja" ]]; then
        ninja clean
        rm -fv ./build.ninja
    fi
    rm -frv ./build
    rm -frv ./**/CMakeFiles
    rm -frv ./.cmake
    rm -fv ./compile_commands.json
    rm -fv ./CMakeCache.txt
    rm -fv ./.ninja_*
    rm -fv ./l61Core/include/l61/l61_config.h
    rm -fv l61-*-x86_64.pkg.tar.zst
    rm -rfv ./l61-*-pak
}

function make_cmd()
{
    if [[ -f "./Makefile" ]]; then
        make $@
    elif [[ -f "./build.ninja" ]]; then
        ninja $@
    fi
}

function make_package()
{
    makepkg -f $@
}

#if [[ "$1" == "clean" ]]; then
#    clean $@
#elif [[ "$1" == "rebuild" || "$1" == "rb" ]]; then
#    rebuild $@
#else
#    build $@
#fi

function check_tools()
{
    command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
    if command -v ninja >/dev/null; then
        CMAKE_GEN="Ninja"
    elif command -v make >/dev/null; then
        echo "No ninja found, falling back to Unix Makefiles"
        CMAKE_GEN="Unix Makefiles"
    else
        echo "Neither ninja nor make found"
        exit 1
    fi
}

check_tools

case "$1" in
    clean | --clean)
        clean "${@:2}"
        ;;
    rebuild|rb | --rebuild|-rb)
        rebuild "${@:2}"
        ;;
    help|h | --help|-h)
        help
        ;;
    make|mk | --make|-mk)
        make_cmd "${@:2}"
        ;;
    check|chk | --check|-chk)
        echo "cmake   : $(command -v cmake || echo not found)"
        echo "ninja   : $(command -v ninja || echo not found)"
        echo "make    : $(command -v make || echo not found)"
        echo "makepkg : $(command -v makepkg || echo not found)"
        ;;
    package| pkg | --package|-pkg )
        make_package "${@:2}"
        ;;
    build|b | --build|-b)
        build "${@:2}"
        ;;
    *)
        build "$@"
        ;;
esac
