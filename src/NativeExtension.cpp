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
// Created by tete on 05/05/2025.
//

#include "NativeExtension.hpp"
#include <dlfcn.h>
#include "defs.hpp"

int NativeExtension::safeExtensionLoad(const std::optional<NativeExtension>& extension, l61_api_extension_t* api, bool required)
{
    if (!extension.has_value())
    {
        if (!required)
        {
            return 1;
        }
        throw std::runtime_error("Extension does not exist");
    }
    return extension->getExtensionEntryPointCall()(api);
}

std::optional<NativeExtension> NativeExtension::extensionLookUp(const std::string& exName)
{
    for (const std::string& _path : mstat.spaths)
    {
        std::string path = _path + "/native/"s + exName;
        if (fs::exists(path))
        {
            return std::make_optional<NativeExtension>(path);
        }
    }
    return {};
}

NativeExtension::NativeExtension(const std::string& path)
: extensionPath(path), soHandle(dlopen(extensionPath.c_str(), RTLD_LAZY))
{
    if (!soHandle)
    {
        throw std::runtime_error(dlerror());
    }
    dlerror();

    this->extensionEntryPointCall = reinterpret_cast<ExtensionEntryPointPtr_t>(dlsym(soHandle, "__l61_rt_ex_init__"));

    char* error = dlerror();
    if (error != nullptr)
    {
        throw std::runtime_error(std::string(error));
    }
}

const NativeExtension::ExtensionEntryPointCall_t& NativeExtension::getExtensionEntryPointCall() const
{
    return this->extensionEntryPointCall;
}

const std::string& NativeExtension::getExtensionPath() const
{
    return extensionPath;
}

NativeExtension::~NativeExtension()
{
    dlclose(soHandle);
}

bool operator==(const NativeExtension& lhs, const NativeExtension& rhs) {
    return lhs.getExtensionPath() == rhs.getExtensionPath();
}

/*namespace std {
    template <>
    struct hash<NativeExtension> {
        std::size_t operator()(const NativeExtension& ext) const noexcept {
            return std::hash<std::string>{}(ext.getExtensionPath());
        }
    };
}*/
