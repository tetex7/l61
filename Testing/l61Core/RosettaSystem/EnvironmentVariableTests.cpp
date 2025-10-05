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
#include <gtest/gtest.h>
#include "l61/RosettaSystem/EnvironmentVariable.hpp"
#include <l61/defs.hpp>
#include <typeinfo>


TEST(EnvironmentVariableTests, ValidEnvironmentVariable)
{
    l61::RosettaSystem::EnvironmentVariable PATH = l61::RosettaSystem::getEnv("PATH");

    EXPECT_TRUE(PATH.exists());
    EXPECT_EQ(PATH.getKey(), "PATH");
    EXPECT_NO_THROW(PATH.getKey());
    EXPECT_NO_THROW(PATH.getValue());
    EXPECT_EQ(PATH.get("fallback"), PATH.getValue());
    EXPECT_EQ(PATH.getValue(), std::getenv("PATH"));
}

TEST(EnvironmentVariableTests, NonValidEnvironmentVariable)
{
    l61::RosettaSystem::EnvironmentVariable know_bad = l61::RosettaSystem::EnvironmentVariable("dsfgdfsdfg");
    EXPECT_ANY_THROW(know_bad.getValue());
    EXPECT_FALSE(know_bad.exists());
    EXPECT_NO_THROW(
        EXPECT_EQ(know_bad.get("fallback"), "fallback")
    );
}