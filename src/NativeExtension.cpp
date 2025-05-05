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

NativeExtension::NativeExtension(const std::string& path)
: extensionPath(path), soHandle(dlopen(extensionPath.c_str(), RTLD_LAZY))
{
    char *error;
    if (!soHandle)
    {
        throw std::runtime_error(dlerror());
    }
    dlerror();

    this->extensionEntryPointCall = reinterpret_cast<ExtensionEntryPointPtr_t>(dlsym(soHandle, "__l61_rt_ex_init__"));

    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
}

const NativeExtension::ExtensionEntryPointCall_t& NativeExtension::getExtensionEntryPointCall()
{
    return this->extensionEntryPointCall;
}

const std::string& NativeExtension::getExtensionPath() const
{
    return extensionPath;
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
