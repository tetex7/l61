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

#include "l61Object.hpp"
#include <typeinfo>
using std::literals::operator ""s;

l61Object::~l61Object() = default;

std::string l61Object::toString() const
{
    return typeid(*this).name();
}

std::size_t l61Object::hashCode() const
{
    return typeid(*this).hash_code();
}
