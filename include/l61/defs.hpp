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
#include "l61/json.hpp"
#include "l61/EventBus.hpp"

#define C_CALL extern "C"
#ifndef LEX61_SYM_LOOKUP_COMPAT
#   define LEX61_SYM_LOOKUP_COMPAT extern "C"
#endif

//Oh, yes this is an abomination, but I like Java and I like to know what am I reading and its purpose
//So the pseudo keywords stay

//Why does this macro exist to help with fast writing of interfaces
//Which are tedious to make when they're all pure virtual if you've done C++ for a long enough time you know
//And the abstract macros or for at a glance reading
//and This is very much so inspired by how COM headers Are written and as well Qt headers

/**
 * @brief denotes that I class is an interface with little to no implementation
 * @note A static analyzer could be designed to use these although usage would have to be self enforced
 */
#define l61_interface struct

/**
 * @brief This denotes that a call within an interface is a pure virtual
 * @param access_level The access level of the function call
 * @param sig Function signature written like prototype
 * @note A static analyzer could be designed to use these although usage would have to be self enforced
 */
#define l61_interface_call(access_level, sig) access_level: virtual sig = 0

/**
 * @brief Create a standard virtual destructor for your interface
 * @param type The interface type
 */
#define l61_interface_deconstructor(type) public: virtual ~type() = default

/**
 * @brief Denotes that the class is abstract with most functions being implemented leaving a few functions to be implemented by inheritors
 */
#define l61_abstract_class class
/**
 * @brief denotes that the method call is not implemented
 * @param sig Function signature written like prototype
 */
#define l61_abstract_call(sig) virtual sig = 0

/**
 * @brief Create a standard virtual destructor for your abstract class
 * @param type The abstract class type
 * @note Is not mandatory but is recommended for simple abstract classes
 */
#define l61_abstract_destructor(type) public: virtual ~type() = default

//Works on clang and GCC Though that's everybody important
//But poor Microsoft the farthest from being standard
//yet cannot even do simple gnu extensions
//NOTE: Experimental use with caution
/*#define l61_interface_cast(type, obj) \
__extension__({ \
static_assert(std::is_base_of_v<type, std::remove_pointer_t<decltype(obj)>>); \
dynamic_cast<type*>(obj); \
})*/

#define l61_interface_cast(type, obj) \
([]<typename T, typename Tp = type>(T _obj) -> Tp* { \
    static_assert(std::is_base_of_v<Tp, std::remove_pointer_t<T>>, "l61_interface_cast type must be a base of the object's type"); \
    return dynamic_cast<Tp*>(_obj); \
})(obj)

#define l61_no_copy(type)        \
type(const type&) = delete; \
type& operator=(const type&) = delete


namespace l61
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
    EventBus eventBus;
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

template <>
struct std::formatter<l61::ScriptMode> : std::formatter<std::string> {
    auto format(const l61::ScriptMode& mode, format_context& ctx) const
    {
        const std::string result = l61::scrModeToStr(mode);
        return std::formatter<std::string>::format(result, ctx);
    }
};
#endif //DEFS_HPP
