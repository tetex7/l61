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
#ifndef L61_UTILS_HPP
#define L61_UTILS_HPP
#include <string>
#include <functional>
#include <type_traits>
#include <vector>
#include <memory>
#include <sstream>

namespace l61
{
    /*template<typename T>
    concept LambdaCall = requires(T t) { //WIP
        // Must be a class with an overloaded operator()
        { &T::operator() } -> std::same_as<auto (T::*)(...) const>;
    };*/
    namespace meta
    {
        template<typename T>
        concept CppObject = std::is_class_v<T>;
    }

    std::vector<char> get_file(const std::string& f_name);
    std::string get_file_str(const std::string& f_name);
    std::string execEx(const char* cmd);
    std::string get_input(const std::string& prompt = "");

    /**
     * @brief Designed to help with C Apis that take function pointers
     * @tparam FunctionSignature The function signature for the Lambda (not a Pointer type)
     * @tparam Lambda The Lambda type
     * @param lambda The Lambda
     * @return A pointer to the Lambda
     */
    template<typename FunctionSignature, typename Lambda>
    std::add_pointer_t<FunctionSignature> lambdaToFunPtr(const Lambda& lambda)
    {
        static_assert(std::is_convertible_v<Lambda, std::add_pointer_t<FunctionSignature>>, "Lambda must be non-capturing and convertible to a function pointer.");
        return static_cast<std::add_pointer_t<FunctionSignature>>(lambda);
    }

    /**
     * @brief Deconstructs an object only use when necessary
     * @tparam T The type to deconstruct
     * @param val The variable to deconstruct
     */
    template<meta::CppObject T>
    [[__gnu__::__always_inline__]]
    constexpr void deconstruct(T& val)
    {
        static_assert(std::is_destructible_v<T>, "Type must be destructible");
        static_assert(not std::is_trivially_destructible_v<T>);
        val.~T();
    }

    template<typename T>
    T runLambda(const std::function<T()>& lambda)
    {
        return std::forward<T>(lambda());
    }

    template<typename T>
    std::string toAddressStrings(const T* ptr)
    {
        std::stringstream ss;
        ss << std::hex << reinterpret_cast<const void*>(ptr);
        return ss.str();
    }

    template<typename T>
    std::size_t getHash(T&& v)
    {
        return std::hash<T>{}(std::forward<T>(v));
    }
}

#endif