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
// Created by tete on 09/02/2025.
//
#pragma once

#ifndef L61_IEVENTBUSCONTAINER_HPP
#define L61_IEVENTBUSCONTAINER_HPP
#include "l61/EventSystem/types.hpp"
#include "l61/EventSystem/Event.hpp"

namespace l61::EventSystem
{
    l61_interface IEventBusContainer
    {
        virtual bool addEvent(const bus_frequency_t& freq, const bus_frequency_t& sub_freq, const Event& event) = 0;
        virtual void removeEvent(const bus_frequency_t& freq, const bus_frequency_t& sub_freq) = 0;

        virtual void removeFrequency(const bus_frequency_t& freq) = 0;

        virtual ~IEventBusContainer() = default;
    };
}

#endif //L61_IEVENTBUSCONTAINER_HPP
