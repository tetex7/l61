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
#ifndef L61_EVENTBUS_HPP
#define L61_EVENTBUS_HPP
#include <cstdint>
#include <map>
#include <variant>
#include <string>
#include <queue>
#include <memory>
#include <set>
#include <format>

#include "l61/Event.hpp"



namespace l61
{
    namespace meta
    {
        /**
         * A type Safeway not to blow your leg off With event frequencies
         */
        template<typename T>
        concept EventBusFrequencyCompatible =
        std::is_same_v<T, std::int32_t> ||
        std::is_same_v<T, std::string> ||
        std::is_convertible_v<T, std::string>; // To appease the compiler for string literals

        template<typename T>
        struct is_eventBus_freq_compatible
        {
            constexpr static bool value = EventBusFrequencyCompatible<T>;
        };
        template<typename T>
        constexpr inline bool is_eventBus_freq_compatible_v = is_eventBus_freq_compatible<T>::value;
    }

    /**
     * @brief This is an event bus leveraging \ref l61::Event
     */
    class EventBus final
    {
    public:
        using bus_frequency_t = std::variant<std::int32_t, std::string>;

    private:
        std::unordered_map<bus_frequency_t, std::unique_ptr<Event>> _map;
        std::queue<bus_frequency_t> _freq_stack;
    public:

        bool addEvent(const bus_frequency_t& freq, const Event& event);
        void removeEvent(const bus_frequency_t& freq);

        void pumpIt();

        void push(const bus_frequency_t& freq);
        void pushBand(const std::set<bus_frequency_t>& freqBand);

        template<meta::EventBusFrequencyCompatible... Ty>
        void pushBand(Ty&&... vals)
        {
            this->pushBand({std::forward<Ty>(vals)...});
        }

        explicit EventBus();
        ~EventBus();

        EventBus(EventBus&&) = delete;
        EventBus(EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;
    };

    //std::ostream& operator<<(std::ostream& stream, s)
} // l61

template <>
struct std::formatter<l61::EventBus::bus_frequency_t> : std::formatter<std::string> {
    auto format(const l61::EventBus::bus_frequency_t& freq, format_context& ctx) const {
        const std::string result = std::visit([]<typename Tp>(const Tp& val) {
            using T = std::decay_t<Tp>;
            if constexpr (std::is_same_v<T, std::string>)
                return std::format("\"{}\"", val);
            else if constexpr (std::is_same_v<T, std::int32_t>)
                return std::format("{}", val);
            else
                return std::format("'{}'", val);
        }, freq);
        return std::formatter<std::string>::format(result, ctx);
    }
};

#endif //L61_EVENTBUS_HPP
