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


/**
 * @file loadSharedLibrary.h
 * @code
 * // Load a library in C99
 * void* handle = l61_rosetta_loadSharedLibrary("./mylib.so");
 * if (!handle) {
 *     printf("Error: %s\n", l61_rosetta_getSharedLibraryLoaderError());
 *     return -1;
 * }
 *
 * // Get a function pointer
 * int (*my_func)(int) = L61_ROSETTA_CAST_SYMBOL(
 *     int(*)(int),
 *     l61_rosetta_getSharedLibrarySymbol(handle, "my_function")
 * );
 *
 * // Use and cleanup
 * if (my_func) {
 *     int result = my_func(42);
 * }
 * l61_rosetta_unloadSharedLibrary(handle);
 * @endcode
 */

#ifndef L61_RS_LOADSHAREDLIBRARY_H
#define L61_RS_LOADSHAREDLIBRARY_H

#include "l61/RosettaSystem/loadSharedLibraryTypes.h"
#ifdef	__cplusplus
#   define L61_ROSETTA_CAST_SYMBOL(type, symbol)  reinterpret_cast<type>(symbol)
#include <stdexcept>
#include <type_traits>
#include <concepts>

namespace l61::RosettaSystem
{
    template<typename T> requires std::is_function_v<T> && (!std::is_pointer_v<T>)
    std::add_pointer_t<T> shared_callable_symbol_cast(l61_rosetta_SharedLibrary_symbol_t symbol)
    {
        if (symbol == nullptr)
        {
            throw std::runtime_error("Symbol is null");
        }
        return L61_ROSETTA_CAST_SYMBOL(std::add_pointer_t<T>, symbol);
    }
}

#else
#   define L61_ROSETTA_CAST_SYMBOL(type, symbol) ((type)(symbol))
#endif


#ifdef	__cplusplus
extern "C" {
#endif
/**
 * Loads a shared library.
 * @param file Path to the library.
 * @return Handle to the loaded library, or NULL on failure.
 */
l61_rosetta_SharedLibrary_handle_t l61_rosetta_loadSharedLibrary(const char *file);

/**
 * Gets a symbol from a shared library.
 * @param handle Handle to the loaded library.
 * @param symbol Name of the symbol to retrieve. (!!Do mind C++ symbol mangling!!)
 * @return Pointer to the requested symbol, or NULL if the symbol is not found.
 */
l61_rosetta_SharedLibrary_symbol_t l61_rosetta_getSharedLibrarySymbol(l61_rosetta_SharedLibrary_handle_t handle, const char* symbol);

/**
 * Unloads a shared library.
 * @param handle Handle to the loaded library.
 * @return 0 on success, -1 on failure.
 */
int l61_rosetta_unloadSharedLibrary(l61_rosetta_SharedLibrary_handle_t handle);

/**
 * Retrieves a description of the last shared library loading error.
 * On POSIX systems, this wraps dlerror(). On Windows, it provides a formatted
 * system error message.
 * @warning The returned string is stored in thread-local storage on POSIX systems
 *          but uses a static buffer on Windows (not thread-safe on Windows).
 * @return A pointer to a string describing the last error. !!DO NOT FREE!!
 */
const char* l61_rosetta_getSharedLibraryLoaderError();

#ifdef	__cplusplus
}
#endif
#endif //L61_RS_LOADSHAREDLIBRARY_H
