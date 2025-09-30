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

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

l61_rosetta_SharedLibrary_handle_t l61_rosetta_loadSharedLibrary(const char *file)
{
    if (!file) return NULL;
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(file);
    return (l61_rosetta_SharedLibrary_handle_t)handle;
#else
    return (l61_rosetta_SharedLibrary_handle_t)dlopen(file, RTLD_LAZY);
#endif
}

l61_rosetta_SharedLibrary_symbol_t l61_rosetta_getSharedLibrarySymbol(l61_rosetta_SharedLibrary_handle_t handle, const char* symbol)
{
    if (!handle || !symbol) return NULL;
#ifdef _WIN32
    return (l61_rosetta_SharedLibrary_symbol_t)GetProcAddress((HMODULE)handle, symbol);
#else
    return (l61_rosetta_SharedLibrary_symbol_t)dlsym(handle, symbol);
#endif
}

int l61_rosetta_unloadSharedLibrary(l61_rosetta_SharedLibrary_handle_t handle)
{
    if (!handle) return -1;
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

