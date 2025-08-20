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

#ifndef L61_SCRIPTENVIRONMENT_HPP
#define L61_SCRIPTENVIRONMENT_HPP

#include <expected>
#include <functional>
#include <stdexcept>

#include "l61/defs.hpp"
#include "sol/sol.hpp"
#include "l61/BaseObjects/Object.hpp"
#include "l61/ScriptEngine/IBasicScriptEngine.hpp"

namespace l61::ScriptEngine
{

l61_abstract_class ScriptEnvironment : public Object, public IBasicScriptEngine
{
private:
    const std::string scriptFilePath;
    l61_stat& scriptCtx;
    sol::state luaCtx;

    AbstractScriptDebugger* script_debugger_;

protected:
    void lib61_setup();
    sol::state& getLuaCtx() override;
    l61_stat& getScriptCtx();

    const std::string& getScriptFilePath() const;

    virtual int run(const std::vector<std::string>& args) = 0;
    virtual void scriptPreInit() = 0;

    explicit ScriptEnvironment(const std::string& scriptFilePath, l61_stat& scriptCtx);

    int standardMainEntryPoint(const std::vector<std::string>& args);

    static sol::table lua_mountLib(const std::string& libraryName, sol::this_state state);

public:
    template<class T>
    void addValue(const std::string& key, T&& value)
    {
        auto var = getLuaCtx()[key] = std::forward<T>(value);
    }


    template<class T>
    T getValue(const std::string& key)
    {
        auto temp = getLuaCtx()[key];
        if ((temp != sol::nil))
        {
            if (temp.is<T>())
            {
                return temp.get<T>();
            }
        }
        throw std::runtime_error(std::format("Value not exist {}", key));
    }

    template<class T>
    void setValue(const std::string& key, const T& value)
    {
        if (auto temp = getLuaCtx()[key]; temp.is<T>())
        {
            temp.set(value);
        }
    }

    bool has(const std::string& key);

    sol::table makeTable(const std::string& name);

    virtual int scriptRun(const std::vector<std::string>& args);

    [[nodiscard]] std::string toString() const override;

    ScriptEnvironment(const ScriptEnvironment&) = delete;
    ScriptEnvironment(ScriptEnvironment&&) = delete;

    ScriptEnvironment& operator=(const ScriptEnvironment&) = delete;

    //Yes this does leak the Lua State what are you going to do bite me
    void specialRun(const std::function<void(sol::state&)>& func) override;

    /**
     * @brief for user input
     * @param code lua code
     */
    void exec(const std::string& code) final;

    void attachDebugger(AbstractScriptDebugger* debugger) override;

    sol::protected_function_result runCodeBlock(const std::string& luaCode) override;

    ~ScriptEnvironment() override;
    friend l61_abstract_class AbstractScriptDebugger;
    friend void standard_lua_debugger_hook(lua_State* L, lua_Debug* D);
};

inline sol::table makeSubTable(const std::string&& name, sol::table table)
{
    sol::table x = table.create_with();
    table.set(std::forward<const std::string>(name), x);
    return x;
}

}

#endif //L61_SCRIPTENVIRONMENT_HPP
