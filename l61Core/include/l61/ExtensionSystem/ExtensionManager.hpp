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
// Created by tete on 05/08/2025.
//
#pragma once
#ifndef L61_EXTENSIONMANAGER_HPP
#define L61_EXTENSIONMANAGER_HPP

#include "l61/ExtensionSystem/NativeExtension.hpp"
#include "l61/ExtensionSystem/ExtensionHeaders.hpp"

namespace l61::ExtensionSystem
{
class ExtensionManager final
{
private:
    HashMap<std::string, std::unique_ptr<NativeExtension>> extension_map;
public:
    explicit ExtensionManager();
    ~ExtensionManager();

    NativeExtension& lookupAndLoadExtension(const std::string& extensionPath, l61_api_extension_ptr api, bool loadEntryPoint = true);

    void unload(const std::string& plugin);

    bool has(const std::string& exName) const;

    const NativeExtension& get(const std::string& exName) const;
    const NativeExtension& operator[](const std::string& exName) const;

    ExtensionManager(ExtensionManager&) = delete;
    ExtensionManager(ExtensionManager&&) = delete;
};
}


#endif //EXTENSIONMANAGER_HPP
