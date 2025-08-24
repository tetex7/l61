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
#pragma once

#ifndef L61_EVENT_SYSTEM_TYPES_HPP
#define L61_EVENT_SYSTEM_TYPES_HPP
#include <cstdint>
#include <type_traits>
#include <string>
#include <variant>

namespace l61::EventSystem
{
    namespace PreDefineEvents
    {
        constexpr inline std::int32_t PRE_LOAD = -40;
        constexpr inline std::int32_t EXT_LOADED = -11;
        constexpr inline const char* T61_TIMER = "com.trs.eventbus.t60";
    };
    using bus_frequency_t = std::variant<std::int32_t, std::string>;
}

namespace l61::meta
{
    /**
     * A type Safeway not to blow your leg off With event frequencies
     */
    template<typename T>
    concept eventBusFrequencyCompatible =
    std::is_same_v<T, std::int32_t> ||
    std::is_same_v<T, std::string> ||
    std::is_convertible_v<T, std::string>; // To appease the compiler for string literals

    template<typename T>
    struct is_eventBus_freq_compatible
    {
        constexpr static bool value = eventBusFrequencyCompatible<T>;
    };
    template<typename T>
    constexpr inline bool is_eventBus_freq_compatible_v = is_eventBus_freq_compatible<T>::value;
}

template <>
struct std::formatter<l61::EventSystem::bus_frequency_t> : std::formatter<std::string> {
    auto format(const l61::EventSystem::bus_frequency_t& freq, format_context& ctx) const {
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

#endif //L61_EVENT_SYSTEM_TYPES_HPP
