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
#include "l61/utils.hpp"

namespace l61::RosettaSystem
{
    EnvironmentVariable::EnvironmentVariable(const std::string& name): name_(name) {}

    std::string EnvironmentVariable::getValue() const
    {
        const char* val = std::getenv(name_.c_str());

        if (!val) throw std::runtime_error(std::format("Environment variable {} does not exist", this->getKey()));

        return {val};
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

    const std::string& EnvironmentVariable::getKey() const
    {
        return name_;
    }

    std::string EnvironmentVariable::toString() const
    {
        return this->get(std::format("[{}=UNSET_ENV_VAR]", this->getKey()));
    }

    std::size_t EnvironmentVariable::hashCode() const
    {
        return getHash(this->getKey());
    }

    nlohmann::json EnvironmentVariable::toJsonValue() const
    {
        return {
            { "key",   this->getKey()   },
            { "value", this->getValue() }
        };
    }

    bool EnvironmentVariable::operator==(const EnvironmentVariable& other) const
    {
        return this->getKey() == other.getKey();
    }

    EnvironmentVariable::EnvironmentVariable(const EnvironmentVariable& environment_variable)
    : name_(environment_variable.name_) {}

    EnvironmentVariable::EnvironmentVariable(EnvironmentVariable&& environment_variable) noexcept
    : name_(std::move(environment_variable.name_)) {}
}

namespace l61::literals
{
    RosettaSystem::EnvironmentVariable operator ""_env(const char* raw_str, const std::size_t len)
    {
        return RosettaSystem::EnvironmentVariable(std::string(raw_str, len));
    }
}