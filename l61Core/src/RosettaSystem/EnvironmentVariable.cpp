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
// Created by tete on 09/15/2025.
//
#include "l61/RosettaSystem/EnvironmentVariable.hpp"
#include <cstdlib>
#include <format>
#include <stdexcept>

namespace l61::RosettaSystem
{
    EnvironmentVariable::EnvironmentVariable(const std::string &name): name_(name) {}

    std::string EnvironmentVariable::getValue() const
    {
        const char* val = std::getenv(name_.c_str());

        if (!val) throw std::runtime_error(std::format("Environment variable {} does not exist", this->getKey()));

        return std::string(val);
    }

    std::string EnvironmentVariable::get(const std::string& defaultValue) const
    {
        const char* val = std::getenv(name_.c_str());
        return val ? std::string(val) : defaultValue;
    }

    bool EnvironmentVariable::exists() const
    {
        return std::getenv(name_.c_str()) != nullptr;
    }

    const std::string & EnvironmentVariable::getKey() const
    {
        return name_;
    }

    std::string EnvironmentVariable::toString() const
    {
        return this->get(std::format("[{}=UNSET_ENV_VAR]", this->getKey()));
    }

    std::size_t EnvironmentVariable::hashCode() const
    {
        return std::hash<std::string>{}(this->getKey());
    }

    bool EnvironmentVariable::operator==(const EnvironmentVariable &other) const
    {
        return this->getKey() == other.getKey();
    }
}