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
// Created by tete on 05/05/2025.
//

#include "l61/meta.hpp"
#include "l61/ExtensionSystem/ExtensionHeaders.hpp"
#include <cassert>


static l61::ExtensionSystem::l61_api_extension_t* raw = l61::null;

using namespace l61;

namespace lex61rt
{ 
    ExtensionSystem::l61_api_extension_ptr getApiData()
    {
        return raw;
    }
}

extern int l61_extension_init();

C_CALL int __l61_rt_ex_init__(ExtensionSystem::l61_api_extension_t* api) // NOLINT(*-reserved-identifier)
{
    assert(api != nullptr && "Null pointer given to API for extension runtime");
    raw = api;
    return l61_extension_init();
}
