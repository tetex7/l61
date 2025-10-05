#!/usr/bin/env bash
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

# shellcheck disable=SC2155
readonly detected_os=$(uname)

if [[ "$detected_os" == "Linux" ]]; then
    readonly DEFAULT_TOOLS=(gcc g++ zip cmake ninja make makepkg git)
elif [[ "$detected_os" == "FreeBSD" ]]; then
    readonly DEFAULT_TOOLS=(clang clang++ zip cmake ninja git)
elif [[ "$detected_os" == "OpenBSD" ]]; then
    readonly DEFAULT_TOOLS=(clang clang++ zip cmake ninja git)
else
    readonly DEFAULT_TOOLS=(gcc g++ zip cmake ninja git)
fi

# If override exists, split it into an array; otherwise use default
if [[ -n "$TRS_TOOL_LIST_OVERRIDE" ]]; then
    # Remove trailing colon if any, then split by colon into array
    IFS=':' read -r -a dev_tools <<< "${TRS_TOOL_LIST_OVERRIDE%:}"
else
    dev_tools=("${DEFAULT_TOOLS[@]}")
fi


#if [[ -z "${CMAKE_GEN}" ]]; then
#    CMAKE_GEN="Ninja"
#fi

function help() {
    echo -e "Dev Setup Script"
    echo "Usage: $0 [clean|release-package|release-package-zip|(check|chk)|(rebuild|rb)|(help|h)|(doxygen|doc)|(arch-package|arch-pkg)|gtest|make|<cmake-args>]"
    echo
    echo "  [--]clean                        Cleans the cmake environment"
    echo "  [--]rebuild | [-]rb              Clean and reconfigure the cmake environment"
    echo "  [--]help    | [-]h               Show this help message"
    echo "  [--]make    | [-]mk              Run the build with detected system"
    echo "  [--]arch-package | [-]arch-pkg   Makes a package using makepkg(Arch)"
    echo "  [--]release-package              Produces a release/testing package"
    echo "  [--]release-package-zip          Produces a release/testing package in a zip"
    echo "  [--]check   |  [-]chk            Checks and output tools availability"
    echo "  [--]build   | [-]b               Build the cmake environment"
    echo "  [--]doxygen | [-]doc             runs doxygen"
    echo "  [--]gtest                        runs gtests"
    echo "  <cmake args>                     Pass-through arguments to cmake"
    echo
    echo "\$TRS_TOOL_CHECK_OVERRIDE : If set to any value but an empty string will Turn off the built in tool checks"
    echo "Unintended side effects is you will have to set \$CMAKE_GEN By hand"
    echo
    echo "\$TRS_TOOL_LIST_OVERRIDE  : Overrides the built in tool list Example TRS_TOOL_LIST_OVERRIDE=\"clang:git\""
    echo
    echo "\$CMAKE_GEN is \"$CMAKE_GEN\" Should be 'Ninja' or 'Unix Makefiles'"
    echo "Detected OS is \"$detected_os\""
    exit 0
}

function rebuild()
{
    "$0" clean
    "$0" "$@"
    exit $?
}

function doxygen_cmd()
{
    doxygen
}

function gtest_run()
{
    "$0" mk
    ctest --stop-on-failure "$@"
}

function build()
{
    #CC=/usr/bin/gcc
    #Ninja
    cmake -G "$CMAKE_GEN" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DL61_CONFIG_DEBUG=ON "$@"  .
}

function make_cmd()
{
    if [[ -f "./Makefile" ]]; then
        make "$@"
    elif [[ -f "./build.ninja" ]]; then
        ninja "$@"
    fi
}

function clean()
{
    make_cmd clean
    if [[ -f "./Makefile" ]]; then
        rm -fv ./Makefile
    elif [[ -f "./build.ninja" ]]; then
        rm -fv ./build.ninja
    fi
    rm -frv ./build
    rm -frv ./.cmake
    rm -fv ./compile_commands.json
    rm -fv ./CMakeCache.txt
    rm -fv ./.ninja_*
    rm -fv ./l61Core/include/l61/l61_config.h
    rm -fv l61-*-x86_64.pkg.tar.zst
    rm -rfv ./l61-deployment-package
    rm -rfv ./Testing/Temporary
    rm -rfv ./docs
    rm -v ./l61-deployment-package.zip

    find "." -maxdepth 20 -type d -name "CMakeFiles" -exec rm -vrf {} +

    find "." -maxdepth 20 -type f -name "CTestTestfile.cmake" -exec rm -vf {} +

    find "." -maxdepth 20 -type f -name "*\[*\]_include.cmake" -exec rm -vf {} +

    find "." -maxdepth 20 -type f -name "*\[*\]_test.cmake" -exec rm -vf {} +

    return 0
}

function make_arch_package()
{
    makepkg -f "$@"
}

function release_package()
{
    ./package.sh
    return $?
}

function release_package_zip()
{
    release_package || return 1

    local folder="l61-deployment-package"
    local zipfile="${folder}.zip"

    if [ -d "$folder" ]; then
        rm -f "$zipfile"
        (cd "$folder" && zip -r "../$zipfile" .)
        echo "Created $zipfile"
    else
        echo "Error: folder '$folder' not found."
        return 1
    fi
    return 0
}

function check_for_commands()
{
    local NFOUND=0

    # figure out max tool name length
    local maxlen=0
    for tool in "${dev_tools[@]}"; do
        (( ${#tool} > maxlen )) && maxlen=${#tool}
    done

    # print aligned results
    for tool in "${dev_tools[@]}"; do
        printf "%-${maxlen}s : " "$tool"
        if command -v "$tool" >/dev/null 2>&1; then
            echo "$(command -v "$tool")"
        else
            echo "not found"
            NFOUND=1
        fi
    done

    if [[ $NFOUND -eq 1 ]]; then
        echo "One or more tools required for compilation could not be found"
        return 1
    fi

    return 0
}

function check_tools()
{
    [[ -n $TRS_TOOL_CHECK_OVERRIDE ]] && { echo -e "Tool check is disabled\ntool based safeguards have been removed\n"; } && return 0
    check_for_commands >/dev/null || { check_for_commands; exit 1; }
    if [[ -z $CMAKE_GEN ]]; then
        if command -v ninja >/dev/null; then
            CMAKE_GEN="Ninja"
        elif command -v make >/dev/null; then
            echo "No ninja found, falling back to Unix Makefiles"
            CMAKE_GEN="Unix Makefiles"
        else
            echo "Neither ninja nor make found"
            exit 1
        fi
    else
        echo "Warning: hand selected cmake generator can error out"
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
        check_for_commands
        exit $?
        ;;
    arch-package|arch-pkg | --arch-package|-arch-pkg )
        make_arch_package "${@:2}"
        ;;
    release-package | --release-package )
        release_package
        ;;
    release-package-zip | --release-package-zip )
        release_package_zip
        ;;
    doxygen|doc | --doxygen|-doc)
        doxygen_cmd "${@:2}"
        ;;
    build|b | --build|-b)
        build "${@:2}"
        ;;
    gtest | --gtest)
        gtest_run "${@:2}"
        ;;
    *)
        build "$@"
        ;;
esac
