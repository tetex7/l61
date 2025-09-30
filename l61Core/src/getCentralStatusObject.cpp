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
// Created by tete on 09/20/2025.
//

#include "l61/defs.hpp"
#include "l61/l61_config.h"

#include "l61/ExtensionSystem/ExtensionManager.hpp"
#include "l61/Logger.hpp"
#include "l61/ExtensionSystem/NativeExtension.hpp"
#include "l61/utils.hpp"
#include "l61/ScriptEngine/AbstractScriptDebugger.hpp"
#include "l61/ScriptEngine/IBasicScriptEngine.hpp"

#include "l61/RosettaSystem/EnvironmentVariable.hpp"
#include "l61/RosettaSystem/getExecutablePath.hpp"
#include "l61/getCentralStatusObject.hpp"

namespace l61
{
using namespace l61::literals;
    l61_stat& getCentralStatusObject()
    {
        static l61_stat mstat = {
            fs::current_path().string(),
            fs::current_path().string() + "/build.l61",
            RosettaSystem::getExecutablePath(),
            "USER"_env.getValue(),
            "HOME"_env.getValue(),
            std::vector {
                ((RosettaSystem::getExecutablePath().parent_path().parent_path() / "lib").string()),
                ("HOME"_env.getValue() + "/.l61_lib"),
                (fs::current_path().string() + "/scripts")
            },
            L61_CONFIG_STR_VERSION,
            ProgramStatus {
                ScriptMode::UndefMode,
                std::make_unique<ExtensionSystem::ExtensionManager>(),
                {},
                0,
                {},
                EventSystem::EventBus()
            }
        };
        return mstat;
    }
}