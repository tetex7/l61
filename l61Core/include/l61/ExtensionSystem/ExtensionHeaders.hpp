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
// Created by tete on 8/11/25.
//
#pragma once

#ifndef L61_EXTENSIONHEADERS_HPP
#define L61_EXTENSIONHEADERS_HPP
#include <memory>
#include <string>
#include <vector>

namespace l61
{
    class ScriptEnvironment;
    struct l61_stat;
}
namespace l61::ExtensionSystem
{
    struct l61_api_extension_t
    {
        l61_stat& l61Ctx;
        std::unique_ptr<ScriptEnvironment> & scriptCtx;
    };

    struct lex61_header_t
    {
        const std::string name;
        const std::vector<std::string> authors;
        const std::string known_compat_version;
    };

    using l61_api_extension_ptr = l61_api_extension_t*;
}
#endif // L61_EXTENSIONHEADERS_HPP
