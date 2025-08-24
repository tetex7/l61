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

#include "l61/EventSystem/Timing/AbstractTimer.hpp"


namespace l61::EventSystem::Timing
{
    AbstractTimer::AbstractTimer(Mode mode) : m_mode(mode) {}
    AbstractTimer::operator bool() const
    {
        return isFinished();
    }
    AbstractTimer::Mode AbstractTimer::getMode() const
    {
        return m_mode;
    }
} // namespace l61::EventSystem::Timing