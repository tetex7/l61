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
// Created by tete on 10/06/2025.
//
#pragma once

#ifndef FS_GETFILTEREDFILEPATH_HPP
#define FS_GETFILTEREDFILEPATH_HPP
#include <filesystem>

namespace fs = std::filesystem;

C_CALL std::string getFilteredFilePath(const fs::path &path);

#endif //GETFILTEREDFILEPATH_HPP
