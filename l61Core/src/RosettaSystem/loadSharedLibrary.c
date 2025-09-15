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

#include "l61/RosettaSystem/loadSharedLibrary.h"


#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

void* l61_rosetta_loadSharedLibrary(const char* file)
{
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(file);
    return (void*)handle;
#else
    return dlopen(file, RTLD_LAZY);
#endif
}

void* l61_rosetta_getSharedLibrarySymbol(void* handle, const char* symbol)
{
#ifdef _WIN32
    return (void*)GetProcAddress((HMODULE)handle, symbol);
#else
    return dlsym(handle, symbol);
#endif
}

int l61_rosetta_unloadSharedLibrary(void* handle)
{
#ifdef _WIN32
    return FreeLibrary((HMODULE)handle) ? 0 : -1;
#else
    return dlclose(handle);
#endif
}

const char* l61_rosetta_getSharedLibraryLoaderError()
{
#ifdef _WIN32
    static char buffer[256];
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, GetLastError(),
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   buffer, sizeof(buffer), NULL);
    return buffer;
#else
    return dlerror();
#endif
}

