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
#include "l61/EventSystem/Timing/AsyncTimer.hpp"
#include <thread>


namespace l61::EventSystem::Timing
{
    AsyncTimer::AsyncTimer(Mode mode) : AbstractTimer(mode) {}

    void AsyncTimer::start(std::uint32_t duration)
    {
        m_finished = false;
        m_task = std::async(std::launch::async, [&] -> void {
            m_running = true;
            if (getMode() == Mode::SECONDS) {
                std::this_thread::sleep_for(std::chrono::seconds(duration));
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(duration));
            }
            m_finished = true;
            m_running = false;
        });
    }

    void AsyncTimer::reset()
    {
        m_finished = false;
    }

    bool AsyncTimer::isFinished() const
    {
        return this->m_finished.load();
    }

    bool AsyncTimer::isRuning() const
    {
        return this->m_running.load();
    }

} // namespace l61::EventSystem::Timing
