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
#include "l61/EventSystem/EventBus.hpp"
#include "l61/Logger.hpp"



namespace l61::EventSystem
{

    bool EventBus::addEvent(const bus_frequency_t& freq, const bus_frequency_t& sub_freq, const Event& event)
    {
        //if (_map[freq].contains(sub_freq)) return false;
        _map[freq][sub_freq] = std::make_unique<Event>(event);
        return true;
    }

    void EventBus::removeEvent(const bus_frequency_t& freq, const bus_frequency_t& sub_freq)
    {
        if (_map.contains(freq))
        {
            _map[freq].erase(sub_freq);
        }
    }

    void EventBus::removeFrequency(const bus_frequency_t &freq)
    {
        if (_map.contains(freq))
        {
            _map.erase(freq);
        }
    }

    void EventBus::pumpIt()
    {
        if (!_map.empty() && !_freq_stack.empty())
        {
            if (const bus_frequency_t& freq = _freq_stack.front(); _map.contains(freq))
            {
                for (const auto& [key, value] : _map[freq])
                {
                    if (const Event& event = *value; static_cast<bool>(event))
                    {
                        event.call();
                    }
                }
            }
            _freq_stack.pop();
        }
    }

    void EventBus::push(const bus_frequency_t& freq)
    {
        _freq_stack.push(freq);
    }

    void EventBus::pushBand(const std::set<bus_frequency_t>& freqBand)
    {
        for (const bus_frequency_t& freq : freqBand)
        {
            this->push(freq);
        }
    }

    void EventBus::addEventBand(const std::set<std::tuple<const bus_frequency_t&, const bus_frequency_t&, const Event&>>& eventBand)
    {
        for (const auto& [freq, sub_freq, event] : eventBand)
        {
            this->addEvent(freq, sub_freq, event);
        }
    }

    EventBus::EventBus() = default;
    EventBus::~EventBus() = default;


    void runEventBus(EventBus& bus, SignalQueue_t& signals)
    {
        if (!signals.empty())
        {
            c_signal_t sig = signals.front();
            signals.pop();
            bus.push(sig);
        }
        bus.pumpIt();
    }
} // l61
