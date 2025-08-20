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

#include "l61/defs.hpp"
#include "l61/ScriptEngine/ScriptEnvironment.hpp"
#include "sol/sol.hpp"
#include "lex61rt.hpp"
#include "l61/ExtensionSystem/ExtensionManager.hpp"


LEX61RT_MAKE_HEADER(
    "lua61",
    { "Tetex7" },
    "1.0.0"
);

struct Lua61EntryPoint : l61::ExtensionSystem::AbstractExtensionEntryPoint
{
    void preLoad() override {}

    int initializer() override
    {
        return 0;
    }

    void unLoad() override {}

    ~Lua61EntryPoint() override = default;
};

LEX61RT_SET_ENTRY_POINT_CLASS(Lua61EntryPoint);