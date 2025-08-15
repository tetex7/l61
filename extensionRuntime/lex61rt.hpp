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

#include "l61/ExtensionSystem/AbstractExtensionEntryPoint.hpp"
#include "l61/ExtensionSystem/ExtensionHeaders.hpp"

namespace lex61rt 
{
    using lex61_header_t = const l61::ExtensionSystem::lex61_header_t;
    extern l61::ExtensionSystem::l61_api_extension_ptr getApiData();
}

extern int l61_extension_init();

#define LEX61RT_MAKE_HEADER(...) \
LEX61_SYM_LOOKUP_COMPAT lex61rt::lex61_header_t __lex61_header__ = { \
    __VA_ARGS__ \
}

LEX61_SYM_LOOKUP_COMPAT {
    extern lex61rt::lex61_header_t __lex61_header__; // NOLINT(*-reserved-identifier)
    extern std::unique_ptr<l61::ExtensionSystem::AbstractExtensionEntryPoint> __lex61_header_ExtensionEntryPoint__; // NOLINT(*-reserved-identifier)
}

namespace lex61rt
{
    template<typename T>
    int set_oop_entry_point()
    {
        if (__lex61_header_ExtensionEntryPoint__ != nullptr)
            throw std::logic_error("OOP entry point already set");

        __lex61_header_ExtensionEntryPoint__ = std::make_unique<T>();
        return 1;
    }
} // namespace lex61rt

#define LEX61RT_SET_ENTRY_POINT_CLASS(type) namespace lex61rt { static volatile int __lex61rt_fake_oop_ep_##type##__ = lex61rt::set_oop_entry_point<type>(); }

#endif