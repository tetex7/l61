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

#ifndef EVENT_HPP
#define EVENT_HPP
#include "defs.hpp"

namespace l61 {

    class Event
    {
    public:
        using callback_t = std::function<int()>;
    private:
        callback_t fun;
    public:
        explicit Event(callback_t function);

        void reset();
        void set(callback_t function);

        int call() const;

        Event(Event&& event) noexcept;

        Event(const Event&) = delete;
        Event(Event&) = delete;

        // ReSharper disable once CppNonExplicitConversionOperator
        /**
         * @brief True if the event has a callback to be called upon
         */
        operator bool() const; // NOLINT(*-explicit-constructor)
    };

} // l61

#endif //EVENT_HPP
