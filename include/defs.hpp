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


#ifndef DEFS_HPP
#define DEFS_HPP

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <filesystem>
#include "sol/sol.hpp"
#include <print>

#define C_CALL extern "C"

namespace fs = std::filesystem;

using std::literals::operator ""s;

using FLAG = bool;

namespace std
{
    template<class K, class V>
    using HashMap = std::unordered_map<K, V>;
}

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

class ConfigRecord final
{
    std::vector<std::string> forceMount;
    std::vector<std::string> extension;
    inline ConfigRecord(){}
    inline ConfigRecord(std::vector<std::string>&& forceMount, std::vector<std::string>&& extension)
    : forceMount(std::forward<std::vector<std::string>>(forceMount)), extension(std::forward<std::vector<std::string>>(extension)){}
};

class ExtensionManager;

struct ProgramStatus
{
    ScriptMode runMode;
    std::unique_ptr<ExtensionManager> extension_manager;
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

using l61_api_extension_ptr = l61_api_extension_t*;

extern std::unique_ptr<ScriptEnvironment> shEnv;
extern l61_stat mstat;

#endif //DEFS_HPP
