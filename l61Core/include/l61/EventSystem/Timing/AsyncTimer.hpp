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

#ifndef L61_ASYNCTIMER_HPP
#define L61_ASYNCTIMER_HPP
#include "l61/EventSystem/Timing/AbstractTimer.hpp"
#include <atomic>

namespace l61::EventSystem::Timing
{
    class AsyncTimer : public AbstractTimer
    {
    private:
        std::atomic<bool> m_finished{false};
        std::atomic<bool> m_running{false};
    public:
        explicit AsyncTimer(Mode mode);
        void start(std::uint32_t duration) override;
        void reset() override;

        bool isFinished() const override;

        bool isRuning() const;

        ~AsyncTimer() override = default;
    };
}

#endif // L61_ASYNCTIMER_HPP
