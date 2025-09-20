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
#pragma once

#ifndef L61_RS_ENVIRONMENT_VARIABLE_HPP
#define L61_RS_ENVIRONMENT_VARIABLE_HPP
#include <string>
#include <l61/BaseObjects/Object.hpp>

namespace l61::RosettaSystem
{
    /**
    * @class EnvironmentVariable
    * @brief A utility class for accessing environment variables by name.
    *
    * This class provides a clean interface to query, check, and retrieve
    * environment variables. It does not modify or set environment variables,
    * only reads them.
    */
    class EnvironmentVariable final : public Object
    {
    private:
        std::string name_;
    public:
        /**
         * @brief Constructs an EnvironmentVariable object with the given name.
         * @param name The name of the environment variable.
         */
        explicit EnvironmentVariable(const std::string& name);

        /**
        * @brief Retrieves the value of the environment variable.
        *
        * @return The value of the environment variable as a \ref std::string.
        *
        * @throws std::runtime_error if the environment variable does not exist.
        *
        * Example:
        * @code
        * EnvironmentVariable path("PATH");
        * std::string pathValue = path.getValue();
        * @endcode
        */
        std::string getValue() const;

        /**
        * @brief Retrieves the value of the environment variable, or returns a default.
        *
        * @param defaultValue The value to return if the environment variable does not exist.
        * @return The value of the environment variable if it exists, otherwise @p defaultValue.
        *
        * Example:
        * @code
        * EnvironmentVariable home("HOME");
        * std::string homeValue = home.get("/tmp");
        * @endcode
        */
        std::string get(const std::string& defaultValue = "") const;

        /**
        * @brief Checks if the environment variable exists.
        *
        * @return true if the environment variable exists, false otherwise.
        *
        * Example:
        * @code
        * EnvironmentVariable editor("EDITOR");
        * if (editor.exists()) {
        *     std::cout << "EDITOR is set." << std::endl;
        * }
        * @endcode
        */
        bool exists() const;

        /**
         * @brief Retrieves the name (key) of the environment variable.
         *
         * @return A constant reference to the name of the environment variable.
         *
         * Example:
         * @code
         * EnvironmentVariable var("LANG");
         * std::cout << "Variable key: " << var.getKey() << std::endl;
         * @endcode
         */
        const std::string& getKey() const;

        std::string toString() const override;

        /**
        * @brief Computes a hash code for this environment variable.
        *
        * The hash is derived from the variable's name, making it suitable for
        * use in hash-based containers (e.g., \ref std::unordered_map).
        *
        * @return A \ref std::size_t value representing the hash code of the variable.
        *
        * Example:
        * @code
        * EnvironmentVariable var("LANG");
        * std::size_t hash = var.hashCode();
        * @endcode
        */
        std::size_t hashCode() const override;


        nlohmann::json toJsonValue() const override;


        /**
        * @brief Equality operator for EnvironmentVariable objects.
        *
        * Two EnvironmentVariable objects are considered equal if they
        * reference the same variable name.
        *
        * @param other Another EnvironmentVariable to compare with.
        * @return true if both objects reference the same environment variable name, false otherwise.
        *
        * Example:
        * @code
        * EnvironmentVariable a("PATH");
        * EnvironmentVariable b("PATH");
        * if (a == b) {
        *     std::cout << "Both refer to the same environment variable." << std::endl;
        * }
        * @endcode
        */
        bool operator==(const EnvironmentVariable& other) const;

        ~EnvironmentVariable() override = default;
    };

    inline EnvironmentVariable getEnv(const std::string& name)
    {
        return EnvironmentVariable(name);
    }
}

namespace l61::literals
{
    RosettaSystem::EnvironmentVariable operator ""_env(const char* raw_str, std::size_t len);
}

#endif //ENVIRONMENTVARIABLE_HPP
