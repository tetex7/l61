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

#include "ExtensionManager.hpp"

ExtensionManager::ExtensionManager() = default;

ExtensionManager::~ExtensionManager() = default;

const NativeExtension& ExtensionManager::lookupAndLoadExtension(const std::string& extensionPath, l61_api_extension_ptr api)
{
    auto exOpt = NativeExtension::extensionLookUp(extensionPath);
    if (exOpt.has_value())
    {
        this->extension_map.emplace(extensionPath, std::move(exOpt.value()));
        exOpt.value().getExtensionEntryPointCall()(api);
    }
    throw std::runtime_error("No extension found during lookup for "s + extensionPath);
}

const NativeExtension& ExtensionManager::operator[](const std::string& exName)
{
    return extension_map[exName];
}
