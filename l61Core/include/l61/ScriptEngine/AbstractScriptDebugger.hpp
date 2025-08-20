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

#pragma once

#ifndef L61_ABSTRACT_SCRIPT_DEBUGGER_HPP
#define L61_ABSTRACT_SCRIPT_DEBUGGER_HPP
#include "sol/sol.hpp"
//#include "l61/defs.hpp"

namespace l61
{
    namespace ScriptEngine
    {
        l61_abstract_class AbstractScriptDebugger;
    }
    struct l61_stat;
    namespace meta
    {
        template<class T>
        concept l61CompatibleScriptDebugger = std::is_base_of_v<ScriptEngine::AbstractScriptDebugger, T>;
    }

    namespace ScriptEngine
    {
        class ScriptEnvironment;

        l61_abstract_class AbstractScriptDebugger
        {
        private:
            ScriptEnvironment* const scriptCtx;
            l61_stat& lstat;
            protected:
            ScriptEnvironment* getScriptCtx();
            l61_stat& getL61Ctx();
            sol::state& getScriptLuaState();
            l61_abstract_call(void preRun(lua_State* L, lua_Debug* D));

            AbstractScriptDebugger(ScriptEnvironment* script, l61_stat& lstat);
        public:
            l61_abstract_call(void run(lua_State* L, lua_Debug* D));

            AbstractScriptDebugger(const AbstractScriptDebugger&) = delete;
            AbstractScriptDebugger& operator=(const AbstractScriptDebugger&) = delete;

            l61_abstract_destructor(AbstractScriptDebugger);
        };
    }
}

#endif