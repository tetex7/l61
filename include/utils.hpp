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
#include "defs.hpp"
#include <functional>

namespace l61
{
    std::vector<char> get_file(const std::string& f_name);
    std::string get_file_str(const std::string& f_name);
    std::string execEx(const char* cmd);

    template<typename T>
    T* lambdaToFunPtr(std::function<T> lambda)
    {
        return lambda.template target<T>();
    }
}

#endif