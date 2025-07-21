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
// Created by tete on 07/20/2025.
//

#include "l61/ShellInterpreterEnvironment.hpp"

namespace l61
{
    ShellInterpreterEnvironment::ShellInterpreterEnvironment(const std::string& scriptFilePath, l61_stat& scriptCtx)
            : ScriptEnvironment(scriptFilePath, scriptCtx)
    {
        this->lib61_setup();
        ShellInterpreterEnvironment::scriptPreInit();
        ScriptEnvironment::getLuaCtx().open_libraries(
                sol::lib::base,
                sol::lib::package,
                sol::lib::coroutine,
                sol::lib::string,
                sol::lib::os,
                sol::lib::math,
                sol::lib::table,
                sol::lib::debug,
                sol::lib::bit32,
                sol::lib::io,
                sol::lib::count
        );
    }

    int ShellInterpreterEnvironment::run(const std::vector<std::string>& args)
    {
        (void)args;
        throw std::runtime_error("interpreter does not have a run function");
    }

    void ShellInterpreterEnvironment::scriptPreInit()
    {

    }
} // l61