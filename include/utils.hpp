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
#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <functional>
#include <type_traits>
#include <vector>

namespace l61
{
    std::vector<char> get_file(const std::string& f_name);
    std::string get_file_str(const std::string& f_name);
    std::string execEx(const char* cmd);

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

    template<typename T>
    T runLambda(const std::function<T()>& lambda)
    {
        return std::forward<T>(lambda());
    }

    template<typename T>
    std::size_t getHash(T&& v)
    {
        return std::hash<T>{}(std::forward<T>(v));
    }

    template<typename T>
    [[__nodiscard__,__gnu__::__always_inline__]]
    constexpr std::remove_reference_t<T>&& copy(T&& val) noexcept
    {
        return std::forward<T>(T(std::forward<T>(val)));
    }
}

#endif