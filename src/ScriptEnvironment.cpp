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
#include "Logger.hpp"
#include "sol/sol.hpp"
namespace l61
{
void ScriptEnvironment::lib61_setup()
{
    auto lb = has("l61") ? getValue<sol::table>("l61") : getLuaCtx().create_named_table("l61");
    lb.set_function("getPwd", []() -> std::string {
        return mstat.work_path;
    });
    lb.set_function("pushEventBus", [](const EventBus::bus_frequency_t& freq) {
        mstat.procStat.eventBus.push(freq);
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
    addValue("mountLib"s, lua_mountLib);
    getLuaCtx().do_file(getScriptFilePath());
    if (getLuaCtx()["main"].is<sol::function>())
    {
        const sol::function sh_main = getLuaCtx()["main"];
        return  sh_main(args.size(), args).get<int>();
    }
    return 1;
}

sol::table ScriptEnvironment::lua_mountLib(const std::string& libraryName, sol::this_state state)
{
    sol::state_view view = {state};
    for (const std::string& path : mstat.spaths)
    {
        if (fs::exists(path + '/' + libraryName + ".lua"))
        {
            auto lib_ret = view.do_file(path + '/' + libraryName + ".lua");
            if ((lib_ret.return_count() == 1) && (lib_ret[0].is<sol::table>()))
            {
                return lib_ret[0].as<sol::table>();
            }
            else
            {
                return sol::nil;
            }
        }
    }
    return sol::nil;
}

sol::table ScriptEnvironment::makeTable(const std::string& name)
{
    return getLuaCtx().create_named_table(name);
}

int ScriptEnvironment::scriptRun(const std::vector<std::string>& args)
{
    lib61_setup();
    this->scriptPreInit();
    return this->run(args);
}

std::string ScriptEnvironment::toString() const
{
    return this->getScriptFilePath();
}

bool ScriptEnvironment::has(const std::string& key)
{
    return getLuaCtx()[key] != sol::nil;
}

void ScriptEnvironment::specialRun(const std::function<void(sol::state&)>& func)
{
    func(getLuaCtx());
}

sol::protected_function_result ScriptEnvironment::runCodeBlock(const std::string& luaCode)
{
    auto* t = l61_interface_cast(IBasicScriptEngine, this);
    return getLuaCtx().do_string(luaCode);
}

ScriptEnvironment::~ScriptEnvironment() = default;
}