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

#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <defs.hpp>
#include <chrono>
#include <ctime>


enum class LogLevel : std::uint8_t
{
    INFO,
    WARN,
    ERROR,
    FATAL
};

template<typename... Ty>
void toLogger(LogLevel level, std::format_string<Ty...> fmt, Ty&&... v_ty)
{

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
    std::println("[{}:{}:{}][{}][{}]: {}",
        now_tm->tm_hour,
        now_tm->tm_min,
        now_tm->tm_sec,
        le,
        "l61-rt",
        std::format(fmt, std::forward<Ty>(v_ty)...)
    );
}



#endif //LOGGER_HPP
