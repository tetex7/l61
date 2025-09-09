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
// Created by tete on 07/21/2025.
//

#include <stdexcept>
#include "l61/Logger.hpp"

extern int l61_main(int argc, const char* argv[]);

int main(int argc, const char** argv)
{
    try
    {
        return l61_main(argc, argv);
    }
    catch (std::exception& e)
    {
        l61::toLogger(nullptr, l61::LogLevel::FATAL, "Unhandled exception: {}", e.what());
        std::exit(1);
    }
}

