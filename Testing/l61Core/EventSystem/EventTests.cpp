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
// Created by tete on 10/04/2025.
//
#include "l61/Logger.hpp"
#include "l61/EventSystem/Event.hpp"
#include <gtest/gtest.h>
#include <l61/defs.hpp>
#include <typeinfo>

static bool test_value = false;
l61::EventSystem::Event test_event = [] -> void {
    test_value = true;
};

TEST(EventTests, TypeAssertions)
{
    EXPECT_TRUE((std::same_as<l61::EventSystem::Event::raw_callback_t, void()>));
    EXPECT_TRUE((std::same_as<l61::EventSystem::Event::callback_t, std::function<void()>>));
}

TEST(EventTests, ValidLifecycle)
{
    EXPECT_TRUE(test_event.valid());
    EXPECT_TRUE(static_cast<bool>(test_event));
    EXPECT_NO_THROW(test_event.call());
    EXPECT_TRUE(test_value);
}

TEST(EventTests, InvalidLifecycle)
{
    EXPECT_NO_THROW(test_event.reset());
    EXPECT_FALSE(test_event.valid());
    EXPECT_FALSE(static_cast<bool>(test_event));
    EXPECT_ANY_THROW(test_event.call());
}