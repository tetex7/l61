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

#include "l61/ExtensionManager.hpp"
namespace l61
{

ExtensionManager::ExtensionManager() = default;

ExtensionManager::~ExtensionManager() = default;

NativeExtension& ExtensionManager::lookupAndLoadExtension(const std::string& extensionPath, l61_api_extension_ptr api, bool loadEntryPoint)
{
    auto exOpt = NativeExtension::extensionLookUp(extensionPath);
    if (exOpt.has_value())
    {
        this->extension_map.emplace(extensionPath, std::make_unique<NativeExtension>(std::move(exOpt.value())));
        if (loadEntryPoint)
        {
            this->extension_map[extensionPath]->getExtensionEntryPointCall()(api);
        }
        return *this->extension_map[extensionPath];
    }
    throw std::runtime_error(std::format("No extension found during lookup for {}", extensionPath));
}

void ExtensionManager::unload(const std::string& plugin)
{
    if (has(plugin))
    {
        this->extension_map.erase(plugin);
    }
}

bool ExtensionManager::has(const std::string& exName) const
{
    return extension_map.contains(exName);
}

const NativeExtension& ExtensionManager::operator[](const std::string& exName) const
{
    if (!has(exName))
    {
        throw std::runtime_error(std::format("extension '{}' has not loaded", exName));
    }
    return *this->extension_map.at(exName);
}

const NativeExtension& ExtensionManager::get(const std::string& exName) const
{
    return (*this)[exName];
}
}