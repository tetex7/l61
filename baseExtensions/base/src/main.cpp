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

#include "l61/Logger.hpp"
#include "l61/NativeExtension.hpp"
#include "l61/defs.hpp"
#include "l61/ScriptEnvironment.hpp"
#include "sol/sol.hpp"
#include "lex61rt.hpp"
#include "l61/ExtensionManager.hpp"
#include <cstdio>
#include <exception>
#include <print>

LEX61RT_MAKE_HEADER(
    "base",
    { "Tetex7" },
    "1.0.0"
);

constexpr const char* extensionload[] =
{
    "fs.lex61",
};

using l61::LogLevel;
using l61::toLogger;

int l61_extension_init()
{
    std::println("ver: {}", lex61rt::getApiData()->l61Ctx.version);
    
    sol::table l61_table = lex61rt::getApiData()->scriptCtx->has("l61") ? lex61rt::getApiData()->scriptCtx->getValue<sol::table>("l61") : lex61rt::getApiData()->scriptCtx->makeTable("l61");

    auto& extension_manager = *lex61rt::getApiData()->l61Ctx.procStat.extension_manager;

    for (const char* const& str : extensionload) 
    {
        try
        {
            auto& ex = extension_manager.lookupAndLoadExtension(str, lex61rt::getApiData(), false);
            if (ex.getExtensionHeader()->authors[0] != "Tetex7"s)
            {
                std::println("no good header for {}", str);
                std::exit(1);
            }
            else
            {
                int rt = ex.getExtensionEntryPointCall()(lex61rt::getApiData());
                if (rt != 0) return rt;
            }
        } 
        catch (std::exception& exception)
        {
            toLogger(LogLevel::ERROR, "{}", exception.what());
        }
    }

    return 0;
}

/*C_CALL int __l61_rt_ex_init__(l61_api_extension_t* api) // NOLINT(*-reserved-identifier)
{
    return l61_extension_init(api);
}*/