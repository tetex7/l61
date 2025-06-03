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

#ifndef SCRIPTENVIRONMENT_HPP
#define SCRIPTENVIRONMENT_HPP

#include <expected>
#include <functional>
#include <stdexcept>

#include "defs.hpp"
#include "sol/sol.hpp"
#include "Object.hpp"
#include "IBasicScriptEngine.hpp"

namespace l61
{

l61_abstract_class ScriptEnvironment : public Object, public IBasicScriptEngine
{
private:
    const std::string scriptFilePath;
    l61_stat& scriptCtx;
    sol::state luaCtx;

    void lib61_setup();
protected:
    sol::state& getLuaCtx() override;
    l61_stat& getScriptCtx();

    const std::string& getScriptFilePath() const;

    l61_abstract_call(int run(const std::vector<std::string>& args));
    l61_abstract_call(void scriptPreInit());

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
            return temp.set(value);
        }
    }

    bool has(const std::string& key);

    sol::table makeTable(const std::string& name);

    virtual int scriptRun(const std::vector<std::string>& args);

    std::string toString() const override;

    ScriptEnvironment(const ScriptEnvironment&) = delete;
    ScriptEnvironment(const ScriptEnvironment&& val) = delete;

    ScriptEnvironment& operator=(const ScriptEnvironment&) = delete;

    //Yes this does leak the Lua State what are you going to do bite me
    void specialRun(const std::function<void(sol::state&)>& func) override;

    sol::protected_function_result runCodeBlock(const std::string& luaCode) override;

    ~ScriptEnvironment() override;
    friend l61_abstract_class AbstractScriptDebugger;
};

}

#endif //SCRIPTENVIRONMENT_HPP
