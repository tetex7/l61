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
// Created by tete on 8/24/25.
//
#pragma once

#ifndef L61_ITIMER_HPP
#define L61_ITIMER_HPP
#include "l61/BaseObjects/Object.hpp"

#include <cstdint>
namespace l61::EventSystem::Timing
{
    l61_abstract_class AbstractTimer : public Object
    {
    public:
        enum class Mode : bool { SECONDS, MILLISECONDS };
    private:
        const Mode m_mode;

    public:
        explicit AbstractTimer(Mode mode = Mode::MILLISECONDS);

        virtual void start(std::uint32_t duration) = 0;
        virtual bool isFinished() const = 0;
        virtual void reset() = 0;

        operator bool() const;
        Mode getMode() const;

        virtual ~AbstractTimer() = default;
    };
}
#endif // L61_ITIMER_HPP
