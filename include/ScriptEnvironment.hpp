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
#include "defs.hpp"
/**
 * @brief  sds
 */
/*abstract*/ class ScriptEnvironment
{
private:
    const std::string scriptFilePath;
    l61_stat& scriptCtx;
    sol::state luaCtx;

    void lib61_setup();
protected:
    l61_stat& getScriptCtx();
    sol::state& getLuaCtx();
    const std::string& getScriptFilePath() const;

    virtual int run(const std::vector<std::string>& args) = 0;
    virtual void scriptPreInit() = 0;

    explicit ScriptEnvironment(const std::string& scriptFilePath, l61_stat& scriptCtx);

    void addTable(std::string& key, sol::table& table);

    int standardMainEntryPoint(const std::vector<std::string>& args);

    template<class T>
    void addValue(std::string& key, T value)
    {
        getLuaCtx()[key] = value;
    }
public:

    int scriptRun(const std::vector<std::string>& args);

    virtual ~ScriptEnvironment();
};



#endif //SCRIPTENVIRONMENT_HPP
