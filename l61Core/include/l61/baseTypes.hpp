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
// Created by tete on 8/17/25.
//

#ifndef L61_BASETYPES_HPP
#define L61_BASETYPES_HPP
#include <queue>
namespace l61
{
    using c_signal_t = int;

    using SignalQueue_t = std::queue<c_signal_t>;

    enum
    {
        FLAG_SET,
        FLAG_UNSET
    };
}

#endif // L61_BASETYPES_HPP
