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
// Created by tete on 8/7/25.
//

#include "l61/Logger.hpp"
#include "l61/ExtensionSystem/ExtensionManager.hpp"
#include "l61/l61_config.h"

#include <gtest/gtest.h>
#include <l61/BaseObjects/Object.hpp>
#include <l61/defs.hpp>

namespace l61
{
//std::unique_ptr<ScriptEnvironment> shEnv;
//std::unique_ptr<AbstractScriptDebugger> luaDugger;


l61_stat mstat = {
    fs::current_path().string(),
    fs::current_path().string() + "/build.l61",
    fs::read_symlink("/proc/self/exe"),
    std::getenv("USER"),
    std::getenv("HOME"),
    std::vector {
        (fs::read_symlink("/proc/self/exe").parent_path().parent_path().string() + "/lib"),
        (std::string(std::getenv("HOME")) + "/.l61_lib"),
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
}

TEST(ObjectTests, BasicAssertions) {
    l61::Object object;
    l61::toLogger(l61::LogLevel::ERROR, "test");
    EXPECT_STREQ(object.typeName().c_str(), "l61::Object");
}