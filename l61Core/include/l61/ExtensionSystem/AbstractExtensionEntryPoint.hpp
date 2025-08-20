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

#ifndef L61_ABSTRACTEXTENSIONENTRYPOINT_HPP
#define L61_ABSTRACTEXTENSIONENTRYPOINT_HPP
#include  <type_traits>

namespace l61::ExtensionSystem
{
    l61_interface AbstractExtensionEntryPoint
    {
        virtual ~AbstractExtensionEntryPoint() = default;
        virtual void preLoad() = 0;
        virtual int initializer() = 0;
        virtual void unLoad() = 0;
    };
}

namespace l61::meta
{
    template<typename T>
    concept extensionEntryPointCompatible = std::is_constructible_v<T, ExtensionSystem::AbstractExtensionEntryPoint>;
}

#endif // L61_ABSTRACTEXTENSIONENTRYPOINT_HPP
