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

#ifndef L61_EVENT_SYSTEM_MESSAGEBUSPACKETS_HPP
#define L61_EVENT_SYSTEM_MESSAGEBUSPACKETS_HPP
#include <l61/meta.hpp>
#include <l61/EventSystem/types.hpp>
#include <string>
#include <variant>
#include <vector>


namespace l61::EventSystem
{
    using packet_message_t = std::variant<
        bool,
        std::uint8_t, std::int8_t,
        std::uint16_t, std::int16_t,
        std::uint32_t, std::int32_t,
        std::uint64_t, std::int64_t,
        std::string
    >;

    struct message_packet_data_t;
}

namespace l61::meta
{
    template<typename T>
    concept isMessageBusCompatible =
        std::same_as<T, bool> ||
        std::same_as<T, std::int8_t>  || std::same_as<T, std::uint8_t> ||
        std::same_as<T, std::int16_t> || std::same_as<T, std::uint16_t> ||
        std::same_as<T, std::int32_t> || std::same_as<T, std::uint32_t> ||
        std::same_as<T, std::int64_t> || std::same_as<T, std::uint64_t> ||
        std::same_as<T, std::string>  ||
        std::convertible_to<T, std::string>; // To appease the compiler for string literals

    template<typename T>
    concept isMessagePacketData = std::same_as<T, EventSystem::message_packet_data_t>;
}

namespace l61::EventSystem
{
#define L61_EVENT_SYSTEM_MSG_PACK_INTS(type) \
type, \
U##type
    enum class message_packet_type : std::uint16_t
    {
        BOOL,
        L61_EVENT_SYSTEM_MSG_PACK_INTS(INT8),
        L61_EVENT_SYSTEM_MSG_PACK_INTS(INT16),
        L61_EVENT_SYSTEM_MSG_PACK_INTS(INT32),
        L61_EVENT_SYSTEM_MSG_PACK_INTS(INT64),
        STRING,
        L61_NULL,
        UNSUPPORTED,
    };
#undef L61_EVENT_SYSTEM_MSG_PACK_INTS

    template<meta::isMessageBusCompatible T>
    consteval message_packet_type get_message_type()
    {
        if constexpr (std::same_as<T, bool>)
            return message_packet_type::BOOL;
        else if constexpr (std::same_as<T, std::int8_t>)
            return message_packet_type::INT8;
        else if constexpr (std::same_as<T, std::uint8_t>)
            return message_packet_type::UINT8;
        else if constexpr (std::same_as<T, std::int16_t>)
            return message_packet_type::INT16;
        else if constexpr (std::same_as<T, std::uint16_t>)
            return message_packet_type::UINT16;
        else if constexpr (std::same_as<T, std::int32_t>)
            return message_packet_type::INT32;
        else if constexpr (std::same_as<T, std::uint32_t>)
            return message_packet_type::UINT32;
        else if constexpr (std::same_as<T, std::int64_t>)
            return message_packet_type::INT64;
        else if constexpr (std::same_as<T, std::uint64_t>)
            return message_packet_type::UINT64;
        else if constexpr (std::convertible_to<T, std::string>)
            return message_packet_type::STRING;
        else
            static_assert(!meta::always_false<T>, "Unsupported type for message_packet_type.");
        return message_packet_type::UNSUPPORTED;
    }

    struct message_packet_data_t
    {
        std::string identifier;
        message_packet_type type;
        packet_message_t message;
        __inline message_packet_data_t(meta::nulling::null_t) // NOLINT(*-explicit-constructor)
        : identifier(meta::null), type(message_packet_type::L61_NULL), message(meta::null) {}

        template<meta::isMessageBusCompatible T>
        static message_packet_data_t of(const std::string& identifier, T&& vl)
        {
            return { identifier, get_message_type<T>(), std::forward<T>(vl) };
        }
    };

    struct message_packet_t
    {
        bus_frequency_t freq;
        std::vector<message_packet_data_t> data;

        template<meta::isMessagePacketData... Ty>
        static message_packet_t of(const bus_frequency_t& freq, Ty&&... pak_datas)
        {
            return {
                freq,
                {
                    std::forward<Ty>(pak_datas)...
                }
            };
        }
    };
}
#endif //L61_EVENT_SYSTEM_MESSAGEBUSPACKETS_HPP
