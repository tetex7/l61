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

#include "l61/NativeExtension.hpp"
#include <stdexcept>
#include <string>
#include "l61/defs.hpp"
#include "l61/Logger.hpp"

#ifdef _WIN32
#include <windows.h>
#undef ERROR

#define RTLD_LAZY   0
#define RTLD_NOW    0
#define RTLD_GLOBAL 0
#define RTLD_LOCAL  0

static inline void* dlopen(const char* file, int mode)
{
    (void)mode; // unused
    HMODULE handle = LoadLibraryA(file);
    return (void*)handle;
}

static inline void* dlsym(void* handle, const char* symbol)
{
    return (void*)GetProcAddress((HMODULE)handle, symbol);
}

static inline int dlclose(void* handle)
{
    return FreeLibrary((HMODULE)handle) ? 0 : -1;
}

static inline const char* dlerror(void)
{
    static char buffer[256];
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, GetLastError(),
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   buffer, sizeof(buffer), NULL);
    return buffer;
}

#else
#include <dlfcn.h>
#endif

#define setup_lock() std::lock_guard<std::mutex> lock(soMutex)

namespace l61
{
int NativeExtension::safeExtensionLoad(const std::expected<NativeExtension, std::string>& extension, l61_api_extension_ptr api, bool required)
{
    if (!extension.has_value())
    {
        if (!required)
        {
            toLogger(LogLevel::ERROR, "{}", extension.error());
            return 1;
        }
        throw std::runtime_error(extension.error());
    }
    return extension->getExtensionEntryPointCall()(api);
}

std::expected<NativeExtension, std::string> NativeExtension::extensionLookUp(const std::string& exName)
{
    for (const std::string& _path : mstat.spaths)
    {
        if (_path == mstat.spaths[2]) continue;
        std::string path = (fs::path(_path) / "native" / exName).string();
        if (fs::exists(path))
        {
            return NativeExtension(path);
        }
    }
    return std::unexpected(std::format("Extension '{}' does not exist", exName));
}
void* NativeExtension::blindSymbolLookup(const std::string& symStr) const
{
    setup_lock();
    dlerror();
    void* ptr = dlsym(soHandle, symStr.c_str());

    const char* error = dlerror();
    if (error != NULL)
    {
        throw std::runtime_error(std::string(error));
    }
    return ptr;
}

void NativeExtension::isGoodExtension() const
{
    if (!this->isValid())
    {
        throw std::runtime_error("Invalid extension access (exmove)");
    }
}

bool NativeExtension::isValid() const
{
    setup_lock();
    return !soHandle ? false : true;
}

NativeExtension::NativeExtension(const std::string& path)
: extensionPath(path), soHandle(dlopen(extensionPath.c_str(), RTLD_LAZY))
{
    if (!soHandle)
    {
        throw std::runtime_error(std::string(dlerror()));
    }
    dlerror();

    this->extensionEntryPointCall = reinterpret_cast<ExtensionEntryPointPtr_t>(blindSymbolLookup(entryPointSymbolName));
    toLogger(LogLevel::INFO, "loaded NativeExtension on path: \"{}\"", path);
}

const NativeExtension::ExtensionEntryPointCall_t& NativeExtension::getExtensionEntryPointCall() const
{
    isGoodExtension();
    setup_lock();
    return this->extensionEntryPointCall;
}

const std::string& NativeExtension::getExtensionPath() const
{
    isGoodExtension();
    setup_lock();
    return extensionPath;
}

const lex61_header_t* NativeExtension::getExtensionHeader() const
{
    auto header = this->extensionSymbolLookup<const lex61_header_t>(headerSymbolName);
    setup_lock();
    if (header.has_value())
    {
        return header.value();
    }
    throw std::runtime_error(std::format("'{}' has no header", this->getExtensionPath()));
}

std::string NativeExtension::toString() const
{
    setup_lock();
    return this->getExtensionPath();
}

NativeExtension::~NativeExtension()
{
    if (soHandle != NULL)
    {
        dlclose(soHandle);
    }
}

NativeExtension::NativeExtension(NativeExtension&& nativeExtension) noexcept
: extensionPath(std::move(nativeExtension.extensionPath)), soHandle(nativeExtension.soHandle), extensionEntryPointCall(std::move(nativeExtension.extensionEntryPointCall))
{
    nativeExtension.soHandle = NULL;
}


bool operator==(const NativeExtension& lhs, const NativeExtension& rhs) {
    return lhs.getExtensionPath() == rhs.getExtensionPath();
}
}
/*namespace std {
    template <>
    struct hash<NativeExtension> {
        std::size_t operator()(const NativeExtension& ext) const noexcept {
            return std::hash<std::string>{}(ext.getExtensionPath());
        }
    };
}*/
