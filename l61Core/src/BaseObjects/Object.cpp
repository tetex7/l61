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

#include "l61/BaseObjects/Object.hpp"

#include <cxxabi.h>
#include <format>
#include <typeinfo>
#include "l61/utils.hpp"
using std::literals::operator ""s;
namespace l61
{

    std::string demangle(const char* mangledName) {
        int status = 0;
        // unique_ptr with custom deleter to free the buffer allocated by __cxa_demangle
        std::unique_ptr<char, void(*)(void*)> demangled(
            abi::__cxa_demangle(mangledName, nullptr, nullptr, &status),
            &std::free
        );

        if (status != 0 || !demangled) {
            throw std::runtime_error("Failed to demangle name");
        }

        return {demangled.get()};
    }

    Object::~Object() = default;

    std::string Object::toString() const
    {
        return  std::format("'{}'@{}", this->typeName(), toAddressStrings(this));
    }

    std::size_t Object::hashCode() const
    {
        return typeid(*this).hash_code();
    }

    std::string Object::typeName() const
    {
        return demangle(typeid(*this).name());
    }

    Object::operator std::string() const
    {
        return this->toString();
    }

}
