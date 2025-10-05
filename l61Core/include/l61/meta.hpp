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
#include <type_traits>
#include <functional>

namespace l61
{
    class Object;
}

namespace l61::meta
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

        //if (obj == nullptr) return nullptr;

        if constexpr (std::same_as<T, Tx>)
            return obj; // Just in case somebody accidentally attempts to cast of the same type

        static_assert(std::is_base_of_v<std::remove_pointer_t<Tx>, std::remove_pointer_t<T>>, "l61::dyn_cast type must be a base of the obj_type's type");
        return static_cast<Tx>(obj);
    }

    template<typename T>
    __inline constexpr T dyn_cast(std::nullptr_t)
    {
        static_assert(std::is_pointer_v<T>, "l61::dyn_cast only works on pointer types");
        return nullptr;
    }

    namespace nulling
    {
        struct null_t;
        class NullableMark
        {
        private:
            const bool is_null_;
        protected:
            explicit NullableMark(bool is_null) : is_null_(is_null){}
        public:
            [[nodiscard]] bool isNull() const { return is_null_; }
            virtual ~NullableMark() = default;
        };
    }


    template<typename T>
    concept isNullableType = !std::same_as<T, nulling::null_t> && (std::default_initializable<T> || std::derived_from<T, nulling::NullableMark>);

    template<typename T>
    concept castToZeroCompatible = requires { (void)static_cast<T>(0); };

    template<typename T, typename C>
    concept canStoreBytesOf = sizeof(T) <= sizeof(C) && (alignof(C) % alignof(T) == 0);

    template<typename T, typename C>
    concept safeCanStoreBytesOf =
    canStoreBytesOf<T, C> &&
    std::is_trivially_copyable_v<T>;

    template<typename T>
    concept stdHashCompatible = requires { {std::hash<T>()(std::declval<T>())} -> std::convertible_to<std::size_t>; };

    namespace nulling
    {
        struct null_t final
        {
            constexpr null_t() = default;
            constexpr null_t(const null_t&) = default;

            template<isNullableType T>
            constexpr operator T() const // NOLINT(*-explicit-constructor)
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

            template<typename T>
            void operator=(T&&) const {}
        };
    }

    template<typename>
    inline constexpr bool always_false = false;

    template<typename>
    inline constexpr bool always_true = true;

    inline constexpr nulling::null_t null;
    using nulling::null_t;
    using nulling::NullableMark;
}

namespace l61
{
    using meta::dyn_cast;
    using meta::null;
}

#endif //L61_META_HPP
