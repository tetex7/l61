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
// Created by tete on 10/05/2025.
//

#include "l61/meta.hpp"
#include <gtest/gtest.h>

struct CustomNullConstructorClass : l61::meta::NullableMark
{
    CustomNullConstructorClass(l61::meta::null_t) noexcept : NullableMark(true) {}
    ~CustomNullConstructorClass() override = default;
};

TEST(NullTests, CustomNullConstructor)
{
    CustomNullConstructorClass test_val = l61::null;
    EXPECT_TRUE(test_val.isNull());
}

TEST(NullTests, NullAssignmentOperator)
{
    EXPECT_NO_THROW(l61::null = 123);
}

TEST(NullTests, ConversionToDefaultInit)
{
    int i = l61::null;        // Should become 0
    EXPECT_EQ(i, 0);

    double d = l61::null;     // Should become 0.0
    EXPECT_EQ(d, 0.0);

    int* p = l61::null;       // Should become nullptr
    EXPECT_EQ(p, nullptr);
}

TEST(NullTests, SinkAssignment)
{
    int x = 42;
    EXPECT_NO_THROW(l61::null = x);      // swallowed
    CustomNullConstructorClass y = l61::null;
    EXPECT_NO_THROW(l61::null = y);      // swallowed
}