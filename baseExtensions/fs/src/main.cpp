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
#include <filesystem>


LEX61RT_MAKE_HEADER(
    "fs",
    { "Tetex7" },
    "1.0.0"
);

struct FsEntryPoint : l61::ExtensionSystem::AbstractExtensionEntryPoint
{
    void preLoad() override {}

    int initializer() override
    {
        auto& script = *lex61rt::getApiData()->scriptCtx;
        auto fs = l61::ScriptEngine::makeSubTable("fs", script.getValue<sol::table>("l61"));

        fs.set_function("exists", [](const std::string path) -> bool {
            return fs::exists(path);
        });

        return 0;
    }

    void unLoad() override {}

    ~FsEntryPoint() override = default;
};

LEX61RT_SET_ENTRY_POINT_CLASS(FsEntryPoint);