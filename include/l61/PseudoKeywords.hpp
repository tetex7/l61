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
// Created by tete on 06/09/2025.
//
#pragma once

#ifndef L61_PSEUDOKEYWORDS_HPP
#define L61_PSEUDOKEYWORDS_HPP

// Oh, yes this is an abomination, but I like Java and I like to know what am I reading and its purpose
// So the pseudo keywords stay

// Why does this macro exist to help with fast writing of interfaces
// Which are tedious to make when they're all pure virtual if you've done C++ for a long enough time you know
// And the abstract macros or for at a glance reading
// and This is very much so inspired by how COM headers Are written and as well Qt headers

// Yes this is force include
// yes when you use my api you're going to have to tell your compiler to force include this

// A rule within this header file of pseudo keywords is that
// all pseudo keywords must distill down to simple real keywords no preprocessor magic

/**
 * @brief denotes that I class is an interface with little to no implementation
 * @note A static analyzer could be designed to use these although usage would have to be self enforced
 */
#define l61_interface struct

/**
 * @brief This denotes that a call within an interface is a pure virtual
 * @param access_level The access level of the function call
 * @param sig Function signature written like prototype
 * @note A static analyzer could be designed to use these although usage would have to be self enforced
 */
#define l61_interface_call(access_level, sig) access_level: virtual sig = 0

/**
 * @brief Create a standard virtual destructor for your interface
 * @param type The interface type
 */
#define l61_interface_deconstructor(type) public: virtual ~type() = default

/**
 * @brief Denotes that the class is abstract with most functions being implemented leaving a few functions to be implemented by inheritors
 */
#define l61_abstract_class class
/**
 * @brief denotes that the method call is not implemented
 * @param sig Function signature written like prototype
 */
#define l61_abstract_call(sig) virtual sig = 0

/**
 * @brief Create a standard virtual destructor for your abstract class
 * @param type The abstract class type
 * @note Is not mandatory but is recommended for simple abstract classes
 */
#define l61_abstract_destructor(type) public: virtual ~type() = default

#define l61_unused [[maybe_unused]]

#endif