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
// Created by tete on 09/10/2025.
//

#include "l61/ScriptEngine/RunnableScriptEnvironment.hpp"


namespace l61::ScriptEngine
{
    RunnableScriptEnvironment::RunnableScriptEnvironment(
        const std::string& scriptFilePath, l61_stat& scriptCtx)
    : FileBackedScriptEnvironment(scriptFilePath, scriptCtx)
    {
    }


    int RunnableScriptEnvironment::standardMainEntryPoint(const std::vector<std::string>& args)
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

    int RunnableScriptEnvironment::scriptRun(const std::vector<std::string>& args)
    {
        lib61_setup();
        this->scriptPreInit();
        return this->run(args);
    }
}