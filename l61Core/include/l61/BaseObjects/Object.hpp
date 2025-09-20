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
#pragma once

#ifndef L61_OBJECT_HPP
#define L61_OBJECT_HPP

#include <string>
#include <type_traits>
#include <utility>
#include <typeinfo>
#include <format>
#include "json.hpp"

namespace l61
{
    class Object;

    namespace meta
    {
        template<class T>
        concept l61Obj = std::is_base_of_v<Object, T>;

        template<class T>
        concept l61ObjPtr = std::is_base_of_v<Object, std::remove_pointer_t<T>>;
    }

    class Object
    {
    public:
        virtual ~Object() = default;

        /**
         * @brief Returns a human-readable string representation of the object.
         *
         * Derived classes should override this to provide a meaningful textual
         * description of their internal state. Default implementation may just
         * return the type name or placeholder text.
         *
         * @return \ref std::string textual representation of the object.
         */
        virtual std::string toString() const;

        /**
         * @brief Returns a hash code for the object.
         *
         * This is useful for putting objects into unordered containers
         * (e.g., `std::unordered_map`, `std::unordered_set`) or for
         * comparisons by value. Derived classes should override this
         * to compute a stable hash of their data.
         *
         * @return \ref std::size_t computed hash value.
         */
        virtual std::size_t hashCode() const;

        /**
         * @brief Returns the demangled name of the type.
         *
         * Provides the runtime name of the object’s dynamic type.
         * Typically uses RTTI (`typeid`) internally and may
         * demangle compiler-specific output.
         *
         * @return \ref std::string name of the dynamic type.
         */
        std::string typeName() const;

        /**
         * @brief Returns RTTI type information object.
         *
         * This returns a reference to `std::type_info` for the
         * actual dynamic type of the object, enabling type-safe
         * runtime comparisons.
         *
         * @return const std::type_info& reference to RTTI info.
         */
        const std::type_info& typeInfo() const;

        /**
         * @brief Serializes the object into JSON form.
         *
         * Intended for persistence, logging, or communication.
         * Derived classes should override this to produce
         * structured JSON output representing their state.
         *
         * @return \ref nlohmann::json JSON representation of the object.
         */
        virtual nlohmann::json toJsonValue() const;

        /**
         * @brief Explicit conversion operator to std::string.
         *
         * Enables syntax like:
         * @code
         * Object* obj = ...;
         * std::string text = static_cast<std::string>(*obj);
         * @endcode
         *
         * By default, this should delegate to `toString()`.
         *
         * @return \ref std::string representation of the object.
         */
        explicit operator std::string() const;
    };

    namespace meta
    {
        template<l61Obj T, l61Obj Ty>
        bool instanceof(const Ty& value)
        {
            return dynamic_cast<const T*>(&value) != nullptr;
        }

        template<l61Obj T, l61Obj Ty>
        bool exact_instanceof(const Ty& value)
        {
            return typeid(T) == value.typeInfo();
        }
    }
}

template <>
struct nlohmann::adl_serializer<l61::Object*>
{
    static void to_json(json& j, const l61::Object* obj) {
        if (obj)
        {
            j = obj->toJsonValue();
        }
        else
        {
            j = nullptr;
        }
    }
};

template <l61::meta::l61Obj T>
struct std::formatter<T> : formatter<std::string> {
    auto format(const T& obj, std::format_context& ctx) const {
        const std::string result = static_cast<const l61::Object&>(obj).toString();
        return std::formatter<std::string>::format(result, ctx);
    }
};

template <l61::meta::l61Obj T>
struct std::hash<T>
{
    std::size_t operator()(const T& obj) const noexcept
    {
        return obj.hashCode();
    }
};


#endif //L61_OBJECT_HPP
