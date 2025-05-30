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
// Created by tete on 05/30/2025.
//
#pragma once
#ifndef EVENTBUS_HPP
#define EVENTBUS_HPP
#include <cstdint>
#include <map>
#include <variant>
#include <string>
#include <queue>
#include <memory>

#include "Event.hpp"

namespace l61
{
    class EventBus final
    {
    public:
        using bus_frequency_t = std::variant<std::int32_t, std::string>;
    private:
        std::unordered_map<bus_frequency_t, std::unique_ptr<Event>> _map;
        std::queue<bus_frequency_t> _freq_stack;
    public:
        void operator()();

        void addEvent(const bus_frequency_t& freq, const Event& event);

        void pumpIt();

        void push(const bus_frequency_t& freq);

        explicit EventBus();
        ~EventBus();

        EventBus(EventBus&&) = delete;
        EventBus(EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;
    };
} // l61

/*template <>
struct std::hash<l61::EventBus::bus_frequency_t> {
    size_t operator()(const l61::EventBus::bus_frequency_t& key) const noexcept {
        return std::visit([](auto&& val) {
            return std::hash<std::decay_t<decltype(val)>>{}(val);
        }, key);
    }
};*/

#endif //EVENTBUS_HPP
