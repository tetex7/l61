/*
 * Copyright (C) 2025  Tetex7
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by tete on 05/01/2025.
//
#pragma once

//Documentation in this header is still work in progress
//Professionalism is not guaranteed And will never be lol

#ifndef DEFS_HPP
#define DEFS_HPP

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>
#include <csignal>
#include <filesystem>
#include <print>
#include <queue>

#include "sol/sol.hpp"
#include "json.hpp"

#define C_CALL extern "C"
#ifndef LEX61_SYM_LOOKUP_COMPAT
#   define LEX61_SYM_LOOKUP_COMPAT extern "C"
#endif

//Oh, yes this is an abomination, but I like Java and I like to know what am I reading and its purpose
//So the pseudo keywords stay

/**
 * @brief denotes that I class is an interface with little to no implementation
 * @note A static analyzer could be designed to use these although usage would have to be self enforced
 */
#define l61_interface struct

/**
 * @brief This denotes that a call within an interface is a pure virtual
 * @param sig Function signature written like prototype
 * @note A static analyzer could be designed to use these although usage would have to be self enforced
 */
#define l61_interface_call(sig) virtual sig = 0

/**
 * @brief Denotes that the class is abstract with most functions being implemented leaving a few functions to be implemented by inheritors
 */
#define l61_abstract_class class
/**
 * @brief denotes that the method call is not implemented
 * @param sig Function signature written like prototype
 */
#define l61_abstract_call(sig) virtual sig = 0

//This one was a good idea when I wrote it not so much anymore
//don't use this it's going to be gone within a few weeks
/**
 * @param sig Function signature written like prototype
 * @deprecated This one was a good idea when I wrote it not so much anymore
 */
#define l61_virtual_call(sig) virtual sig

//We do not talk about this abomination
namespace std
{
    template<class K, class V>
    using HashMap = std::unordered_map<K, V>;
}

//End of abomination

namespace fs = std::filesystem;

using std::literals::operator ""s;

namespace l61
{

using flag_t = bool;

enum class ScriptMode : std::uint8_t
{
    UndefMode = 0,
    ShellScriptMode,
    BuildScriptMode
};

__inline std::string scrModeToStr(ScriptMode script_mode)
{
    switch (script_mode)
    {
        case ScriptMode::ShellScriptMode:
            return "ScriptMode::ShellScriptMode"s;
        case ScriptMode::BuildScriptMode:
            return "ScriptMode::BuildScriptMode"s;
        default:
            return "ScriptMode::UndefMode"s;
    }
}


__inline ScriptMode toScriptMode(const std::string& str)
{
    if (str == "shell")
    {
        return ScriptMode::ShellScriptMode;
    }
    if (str == "build")
    {
        return ScriptMode::BuildScriptMode;
    }
    return ScriptMode::UndefMode;
}


template<typename... vT>
[[__gnu__::__always_inline__]] __inline void cout_print(const vT&... vals)
{
    (std::cout << ... << vals);
}

struct ConfigRecord final
{
    std::vector<std::string> forceMount;
    std::vector<std::string> extension;
    __inline ConfigRecord(){}
    __inline ConfigRecord(std::vector<std::string>&& forceMount, std::vector<std::string>&& extension)
    : forceMount(std::forward<std::vector<std::string>>(forceMount)), extension(std::forward<std::vector<std::string>>(extension)){}
};

class ExtensionManager;

struct config_t
{
    std::vector<std::string> spaths;
    std::vector<std::string> plugins;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(config_t, spaths, plugins);
};

using c_signal_t = int;

struct ProgramStatus
{
    ScriptMode runMode;
    std::unique_ptr<ExtensionManager> extension_manager;
    config_t config;
    flag_t verbose;
    std::queue<c_signal_t> signalStack; // Yes, yes I know it's not a stack but the semantics are how I like my stacks
};

struct l61_stat
{
    std::string work_path;
    std::string make_file_path;
    std::string bin_path;
    std::string user_name;
    std::string user_home;
    std::vector<std::string> spaths;
    const std::string version;
    ProgramStatus procStat;
};

class ScriptEnvironment;

struct l61_api_extension_t
{
    l61_stat& l61Ctx;
    std::unique_ptr<ScriptEnvironment>& scriptCtx;
};

struct lex61_header_t
{
    const std::string name;
    const std::vector<std::string> authors;
    const std::string known_compat_version;
};

using l61_api_extension_ptr = l61_api_extension_t*;

l61_abstract_class AbstractScriptDebugger;

extern std::unique_ptr<ScriptEnvironment> shEnv;
extern l61_stat mstat;
extern std::unique_ptr<AbstractScriptDebugger> luaDugger;

}
#endif //DEFS_HPP
