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

//
// Created by tete on 05/22/2025.
//

#ifndef L61_EVENT_HPP
#define L61_EVENT_HPP
#include <functional>

namespace l61 {

    class Event
    {
    public:
        using callback_t = std::function<void()>;
    private:
        callback_t fun;
    public:

        explicit Event(const callback_t& function);

        // ReSharper disable once CppNonExplicitConvertingConstructor
        template<typename Lambda>
        Event(const Lambda& lambda) : fun(lambda){}// NOLINT(*-explicit-constructor)

        void reset();
        void set(const callback_t& function);

        void call() const;

        Event(Event&& event) noexcept;
        Event(const Event& event);

        // ReSharper disable once CppNonExplicitConversionOperator
        /**
         * @brief True if the event has a callback to be called upon
         */
        operator bool() const; // NOLINT(*-explicit-constructor)
    };

} // l61

#endif //EVENT_HPP
