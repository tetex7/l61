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

#include "ScriptEnvironment.hpp"

void ScriptEnvironment::lib61_setup()
{
    auto lb = getLuaCtx().create_named_table("l61");
    lb.set_function("getPwd", []() {
        return mstat.work_path;
    });
}

l61_stat& ScriptEnvironment::getScriptCtx()
{
    return this->scriptCtx;
}

sol::state& ScriptEnvironment::getLuaCtx()
{
    return this->luaCtx;
}

const std::string& ScriptEnvironment::getScriptFilePath() const
{
    return this->scriptFilePath;
}

ScriptEnvironment::ScriptEnvironment(const std::string& scriptFilePath, l61_stat& scriptCtx)
    : scriptFilePath(scriptFilePath), scriptCtx(scriptCtx), luaCtx(sol::state()) {}

int ScriptEnvironment::standardMainEntryPoint(const std::vector<std::string>& args)
{
    getLuaCtx().do_file(getScriptFilePath());
    if (getLuaCtx()["main"].is<sol::function>())
    {
        const sol::function sh_main = getLuaCtx()["main"];
        return  sh_main(args.size(), args).get<int>();
    }
    return 1;
}

int ScriptEnvironment::scriptRun(const std::vector<std::string>& args)
{
    lib61_setup();
    this->scriptPreInit();
    return this->run(args);
}

ScriptEnvironment::~ScriptEnvironment() = default;
