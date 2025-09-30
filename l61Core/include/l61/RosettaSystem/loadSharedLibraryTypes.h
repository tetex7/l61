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
// Created by tete on 09/30/2025.
//

#ifndef L61_RS_LOADSHAREDLIBRARYTYPES_H
#define L61_RS_LOADSHAREDLIBRARYTYPES_H
#ifdef	__cplusplus
extern "C" {
#endif

// Opaque handle type for loaded libraries
typedef void* l61_rosetta_SharedLibrary_handle_t;

// Function pointer type for generic symbols
typedef void (*l61_rosetta_SharedLibrary_symbol_t)(void);

#ifdef	__cplusplus
}
#endif

#endif //LOADSHAREDLIBRARYTYPES_H
