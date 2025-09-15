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

#ifndef L61_RS_LOADSHAREDLIBRARY_H
#define L61_RS_LOADSHAREDLIBRARY_H
#ifdef	__cplusplus
extern "C" {
#endif
/**
 * Loads a shared library.
 * @param file Path to the library.
 * @return Handle to the loaded library, or NULL on failure.
 */
void* l61_rosetta_loadSharedLibrary(const char* file);

/**
 * Gets a symbol from a shared library.
 * @param handle Handle to the loaded library.
 * @param symbol Name of the symbol to retrieve. (!!Do mind C++ symbol mangling!!)
 * @return Pointer to the requested symbol, or NULL if the symbol is not found.
 */
void* l61_rosetta_getSharedLibrarySymbol(void* handle, const char* symbol);

/**
 * Unloads a shared library.
 * @param handle Handle to the loaded library.
 * @return 0 on success, -1 on failure.
 */
int l61_rosetta_unloadSharedLibrary(void* handle);

/**
 * Retrieves a description of the last shared library loading error.
 * On POSIX systems, this wraps dlerror(). On Windows, it provides a formatted
 * system error message.
 * @return A pointer to a string describing the last error. !!DO NOT FREE!!
 */
const char* l61_rosetta_getSharedLibraryLoaderError();

#ifdef	__cplusplus
}
#endif
#endif //L61_RS_LOADSHAREDLIBRARY_H
