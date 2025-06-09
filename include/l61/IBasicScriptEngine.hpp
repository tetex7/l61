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
// Created by tete on 06/01/2025.
//
#pragma once

#ifndef L61_IBASICSCRIPTENGINE_HPP
#define L61_IBASICSCRIPTENGINE_HPP
#include "AbstractScriptDebugger.hpp"

namespace l61
{
    l61_interface IBasicScriptEngine
    {
        l61_interface_call(protected, sol::state& getLuaCtx());

        /**
         * @brief Runs arbitrary lua code from a string
         * @param luaCode String containing lua code
         * @return Returns the function results of the Lua code
         */
        l61_interface_call(public, sol::protected_function_result runCodeBlock(const std::string& luaCode));

        /**
         * @brief Allows you to run arbitrary code involving the Script state
         * @param func A lambda or a function To run your arbitrary code
         * @note This does leak the lua state
         */
        l61_interface_call(public, void specialRun(const std::function<void(sol::state&)>& func));

        /**
         * @brief Attach a debugger to this script environment
         * @param debugger Pointer to a debugger
         */
        l61_interface_call(public, void attachDebugger(AbstractScriptDebugger* debugger));

        l61_interface_deconstructor(IBasicScriptEngine);
    };
}

#endif //IBASICSCRIPTENGINE_HPP
