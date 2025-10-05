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
// Created by tete on 05/22/2025.
//

#include "l61/EventSystem/Event.hpp"

namespace l61::EventSystem
{
    Event::Event(const callback_t& function)
        : fun(function) {}

    void Event::reset()
    {
        fun = callback_t();
    }

    bool Event::valid() const
    {
        return static_cast<bool>(fun);
    }

    void Event::set(const callback_t& function)
    {
        fun = function;
    }

    void Event::call() const
    {
        fun();
    }

    Event::Event(Event&& event) noexcept
    : fun(std::move(event.fun)) {}

    Event::Event(const Event& event)
    : fun(event.fun){}


    Event::operator bool() const
    {
        return valid();
    }
} // l61