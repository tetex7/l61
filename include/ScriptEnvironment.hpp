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

#include "sol/sol.hpp"
#include <optional>
#include <stdexcept>

#include "defs.hpp"
#include "l61Object.hpp"

namespace l61
{

/*abstract*/ class ScriptEnvironment : public l61Object
{
private:
    const std::string scriptFilePath;
    l61_stat& scriptCtx;
    sol::state luaCtx;

    void lib61_setup();
protected:
    sol::state& getLuaCtx();
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
        throw std::runtime_error(std::format("Value not exst {}", key));
    }

    template<class T>
    void setValue(const std::string& key, const T& value)
    {
        auto temp = getLuaCtx()[key];
        if (temp.is<T>())
        {
            return temp.set(value);
        }
    }

    bool has(const std::string& key);

    sol::table makeTable(const std::string& name);

    virtual int scriptRun(const std::vector<std::string>& args);

    std::string toString() const override;

    ~ScriptEnvironment() override;
};

}

#endif //SCRIPTENVIRONMENT_HPP
