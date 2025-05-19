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

#include "defs.hpp"
#include "ScriptEnvironment.hpp"
#include "sol/sol.hpp"
#include "lex61rt.hpp"
#include "ExtensionManager.hpp"

LEX61RT_MAKE_HEADER(
    "fs",
    { "Tetex7" },
    "1.0.0"
);

int l61_extension_init()
{
    return 0;
}

/*C_CALL int __l61_rt_ex_init__(l61_api_extension_t* api) // NOLINT(*-reserved-identifier)
{
    return l61_extension_init(api);
}*/