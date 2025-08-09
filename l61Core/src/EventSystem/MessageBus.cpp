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
// Created by tete on 07/23/2025.
//

#include "l61/EventSystem/MessageBus.hpp"

#include <stdexcept>

namespace l61::EventSystem
{
    void MessageBus::push(message_packet_data_t&& packet)
    {
        (void)packet;
        _packets.push_back(std::forward<message_packet_data_t>(packet));
    }

    void MessageBus::pop()
    {
        _packets.pop();
    }

    message_packet_data_t& MessageBus::peek()
    {
        if (_packets.empty())
            throw std::runtime_error("MessageBus::peek() called on empty queue.");
        return _packets.front();
    }
} // EventSystem