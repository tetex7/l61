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

#pragma once
#ifndef LEX61RT_HPP
#define LEX61RT_HPP

#define LEX61_SYM_LOOKUP_COMPAT extern "C"

#include "defs.hpp"

namespace lex61rt 
{
    using lex61_header_t = const ::lex61_header_t;
    extern l61_api_extension_ptr getApiData();
}

#define LEX61RT_MAKE_HEADER(...) \
LEX61_SYM_LOOKUP_COMPAT lex61rt::lex61_header_t __lex61_header__ = { \
    __VA_ARGS__ \
}

LEX61_SYM_LOOKUP_COMPAT {
    extern lex61rt::lex61_header_t __lex61_header__;
}

#endif