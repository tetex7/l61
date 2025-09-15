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

#include <cstdio>
#include <exception>
#include <print>

#include "l61/Logger.hpp"
#include "l61/ExtensionSystem/NativeExtension.hpp"
#include "l61/defs.hpp"
#include "l61/ScriptEngine/ScriptEnvironment.hpp"
#include "l61/ScriptEngine/RunnableScriptEnvironment.hpp"
#include "sol/sol.hpp"
#include "lex61rt.hpp"
#include "l61/ExtensionSystem/ExtensionManager.hpp"

#include "l61/l61_config.h"

LEX61RT_MAKE_HEADER(
    "base",
    { "Tetex7" },
    L61_CONFIG_STR_VERSION
);

constexpr const char* extensionLoad[] = {
    "fs.lex61",
};

using l61::LogLevel;

struct BaseEntryPoint : l61::ExtensionSystem::AbstractExtensionEntryPoint
{
    void preLoad() override {}
    int initializer() override
    {
        std::println("ver: {}", lex61rt::getApiData()->l61Ctx.version);

        sol::table l61_table = lex61rt::getApiData()->scriptCtx->has("l61") ? lex61rt::getApiData()->scriptCtx->getValue<sol::table>("l61") : lex61rt::getApiData()->scriptCtx->makeTable("l61");

        auto& extension_manager = *lex61rt::getApiData()->l61Ctx.procStat.extension_manager;

        for (const char* const& str : extensionLoad)
        {
            try
            {
                if (auto& ex = extension_manager.lookupAndLoadExtension(lex61rt::getApiData()->l61Ctx.spaths, str, lex61rt::getApiData(), false); ex.getExtensionHeader()->authors[0] != "Tetex7"s)
                {
                    extension_manager.unload(str);
                    std::println("no good header for {}", str);
                    l61::toLogger(nullptr, LogLevel::ERROR, "Cannot find well formed {}", str);
                }
                else
                {
                    int rt = ex.getExtensionEntryPointCall()(lex61rt::getApiData());
                    if (rt != 0) return rt;
                }
            }
            catch (std::exception& exception)
            {
                l61::toLogger(nullptr, LogLevel::ERROR, "{}", exception.what());
            }
        }

        return 0;
    }
    void unLoad() override {}

    ~BaseEntryPoint() override = default;
};

LEX61RT_SET_ENTRY_POINT_CLASS(BaseEntryPoint);