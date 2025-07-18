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
// Created by tete on 07/15/2025.
//

#ifndef L61_META_HPP
#define L61_META_HPP
#include <concepts>

#include "meta.hpp"
#include "meta.hpp"
#include "meta.hpp"

namespace l61
{
    class Object;
}

namespace l61
{
    template<
        typename cast_type, // The only mandatory template parameter The rest can be inferred
        typename obj_type,
        typename T = obj_type, // A leftover from an older rendition Since it's a compile time thing it will not be removed
        typename Tx = std::conditional_t<std::is_pointer_v<cast_type>, cast_type, std::add_pointer_t<cast_type>>
    >
    __inline constexpr Tx dyn_cast(obj_type obj)
    {
        static_assert(std::is_pointer_v<T>, "l61::dyn_cast only works on pointer types");

        if constexpr (obj == nullptr) return nullptr;

        if constexpr (std::same_as<T, Tx>)
            return obj; // Just in case somebody accidentally attempts to cast of the same type

        static_assert(std::is_base_of_v<std::remove_pointer_t<Tx>, std::remove_pointer_t<T>>, "l61::dyn_cast type must be a base of the obj_type's type");
        return static_cast<Tx>(obj);
    }

    struct null_t;

    template<typename T>
    concept isNullableType = std::default_initializable<T> || std::is_constructible_v<T, null_t>;

    template<typename T>
    concept castToZeroCompatible = requires { (void)static_cast<T>(0); };

    struct null_t final
    {
        //I don't know why I add this, but it might come in handy
        template<isNullableType T>
        constexpr null_t(T){} // NOLINT(*-explicit-constructor)

        constexpr null_t() = default;

        template<isNullableType T>
        __inline consteval operator T() const // NOLINT(*-explicit-constructor)
        {
            if constexpr (std::default_initializable<T>)
            {
                if constexpr (castToZeroCompatible<T>)
                    return static_cast<T>(0);
                else if constexpr (std::is_pointer_v<T>)
                    return nullptr;
                return T();
            }
            return T(null_t());
        }

        template<isNullableType T>
        __inline consteval void operator=(T){} // NOLINT(*-unconventional-assign-operator)
    };
    __inline constexpr null_t null;
}

#endif //L61_META_HPP
