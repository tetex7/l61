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

#ifndef L61_DEFS_HPP
#define L61_DEFS_HPP

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
#include "EventSystem/EventBus.hpp"
#include "l61/baseTypes.hpp"

//Works on clang and GCC Though that's everybody important
//But poor Microsoft the farthest from being standard
//yet cannot even do simple gnu extensions
//NOTE: Experimental use with caution
/*#define l61_interface_cast(type, obj) \
__extension__({ \
static_assert(std::is_base_of_v<type, std::remove_pointer_t<decltype(obj)>>); \
dynamic_cast<type*>(obj); \
})*/

#include <l61/meta.hpp>


#define l61_interface_cast(type, obj) l61::dyn_cast<type, decltype(obj)>(obj)
/*([]< \
typename R = decltype(obj), \
typename Rp = type, \
typename T = std::conditional_t<std::is_pointer_v<R>, R, std::add_pointer_t<R>>, \
typename Tx = std::conditional_t<std::is_pointer_v<Rp>, Rp, std::add_pointer_t<Rp>>>(T _obj) -> Tx { \
    static_assert(std::is_base_of_v<std::remove_pointer_t<Tx>, std::remove_pointer_t<T>>, "l61_interface_cast type must be a base of the object's type"); \
    return static_cast<Tx>(_obj); \
})((obj))*/


#define l61_no_copy(type)        \
type(const type&) = delete; \
type& operator=(const type&) = delete


namespace l61
{
    template<class K, class V>
    using HashMap = std::unordered_map<K, V>;

    template<typename... T>
    using AutoPointer = std::unique_ptr<T...>;
}

//End of abomination

namespace fs = std::filesystem;

using std::literals::operator ""s;

namespace l61
{

    using flag_t = std::uint8_t;

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

    namespace ExtensionSystem
    {
        class ExtensionManager;
    }

    struct ConfigRecord final
    {
        std::vector<std::string> spaths; // Search path to be appended to built-in
        std::vector<std::string> extension; // Native (*.lex61) Extensions to be autoloaded
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigRecord, spaths, extension);
    };

    struct ProgramStatus final
    {
        ScriptMode runMode;
        std::unique_ptr<ExtensionSystem::ExtensionManager> extension_manager;
        ConfigRecord config;
        flag_t verbose;
        SignalQueue_t signalQueue;
        EventSystem::EventBus eventBus;
    };

    struct l61_stat final
    {
        std::string work_path;
        std::string make_file_path;
        std::string bin_path;
        std::string user_name;
        std::string user_home;
        std::vector<std::string> spaths;
        const std::string version;
        ProgramStatus procStat;

        operator l61_stat*() // NOLINT(*-explicit-constructor)
        {
            return this;
        }
    };
    namespace ScriptEngine
    {
        l61_abstract_class AbstractScriptDebugger;
    }

    extern l61_stat mstat;
}

template <>
struct std::formatter<l61::ScriptMode> : std::formatter<std::string> {
    auto format(const l61::ScriptMode& mode, format_context& ctx) const
    {
        const std::string result = l61::scrModeToStr(mode);
        return std::formatter<std::string>::format(result, ctx);
    }
};
#endif //L61_DEFS_HPP
