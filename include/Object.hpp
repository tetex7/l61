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
// Created by tete on 05/13/2025.
//

#ifndef L61OBJECT_HPP
#define L61OBJECT_HPP

#include <string>
#include <type_traits>
#include <utility>
#include <format>
namespace l61
{
    class Object;

    namespace meta
    {
        template<class T>
        concept l61Obj = std::is_base_of_v<Object, T>;
    }


    class Object
    {
    public:
        virtual ~Object();

        virtual std::string toString() const;
        virtual std::size_t hashCode() const;
        explicit operator std::string() const;
    };
}

template <l61::meta::l61Obj T>
struct std::formatter<T> : formatter<std::string> {
    auto format(const T& obj, std::format_context& ctx) const {
        const std::string result = static_cast<const l61::Object&>(obj).toString();
        return std::formatter<std::string>::format(result, ctx);
    }
};

#endif //L61OBJECT_HPP
