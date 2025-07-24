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
// Created by tete on 05/13/2025.
//
#pragma once

#ifndef L61_LOGGER_HPP
#define L61_LOGGER_HPP
#include <l61/defs.hpp>
#include <chrono>
#include <ctime>
#include <format>

namespace l61
{
enum class LogLevel : std::uint8_t
{
    INFO,
    WARN,
    ERROR,
    FATAL
};

/**
 *
 * @tparam Ty Types of arguments passed to be logged
 * @param level The logging output level e.g \ref LogLevel::WARN
 * @param fmt The format string using modern C++23 std::format
 * @param args Values to be logged
 */
template<typename... Ty>
void toLogger(LogLevel level, std::format_string<Ty...> fmt, Ty&&... args)
{
    if (!mstat.procStat.verbose && ((level == LogLevel::WARN) || (level == LogLevel::INFO))) return;
    std::string le;
    switch (level)
    {
        case LogLevel::INFO:
            le = "INFO";
            break;
        case LogLevel::WARN:
            le = "WARN";
            break;
        case LogLevel::ERROR:
            le = "ERROR";
            break;
        case LogLevel::FATAL:
            le = "FATAL";
            break;
    }

    auto now = std::chrono::system_clock::now();

    // Convert to time_t to use with std::localtime
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure for broken-down time
    std::tm* now_tm = std::localtime(&now_time_t);

    decltype(std::cout)* v = &std::cout;

    if (static_cast<std::uint8_t>(LogLevel::ERROR) <= static_cast<std::uint8_t>(level))
    {
        v = &std::cerr;
    }

    std::println(
        *v,
        "[{}:{}:{}][{}][{}]: {}",
        now_tm->tm_hour,
        now_tm->tm_min,
        now_tm->tm_sec,
        le,
        "l61-rt",
        std::format(fmt, std::forward<Ty>(args)...)
    );
}

}

#endif //LOGGER_HPP
