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
#pragma once

#ifndef L61_NATIVEEXTENSION_HPP
#define L61_NATIVEEXTENSION_HPP
#include <expected>
#include <mutex>
#include <stdexcept>
#include <type_traits>

#include "l61/defs.hpp"
#include "l61/BaseObjects/Object.hpp"

namespace l61
{
/**
 * @brief Handling native extensions
 */
class NativeExtension final : public Object
{
public:
    /**
     * @brief The standard entry point for an extension usually defined by the extension runtime
     */
    static constexpr const char* entryPointSymbolName = "__l61_rt_ex_init__";

    /**
     * @brief The symbol name for the extension header this must be self defined
     */
    static constexpr const char* headerSymbolName = "__lex61_header__";

    using ExtensionEntryPoint_t = int(l61_api_extension_ptr);
    using ExtensionEntryPointPtr_t = std::add_pointer_t<ExtensionEntryPoint_t>;
    using ExtensionEntryPointCall_t = std::function<ExtensionEntryPoint_t>;
private:
    std::string extensionPath;

    /**
     * @brief an OS dependent handle to a shared library
     * @note Praise be to Linux dynamic linker
     */
    void* soHandle;
    ExtensionEntryPointCall_t extensionEntryPointCall;

    /**
     * @brief A mutex for a slight safety
     */
    mutable std::mutex soMutex;

    /**
     * @brief Horrifically unsafe and that's why it's private
     * @param symStr The name of the symbol
     * @return Returns a raw void pointer to that symbol
     */
    [[nodiscard]] void* blindSymbolLookup(const std::string& symStr) const;

    void isGoodExtension() const;
public:
    /**
     * @brief Safely loads an extension
     * @param extension Fill in with the result of the lookup
     * @param api Fill in with a pointer to the api exchange structure
     * @param required Do you care if this extension is not loaded
     * @return The return value of the entry point
     */
    static int safeExtensionLoad(const std::expected<NativeExtension, std::string>& extension, l61_api_extension_ptr api, bool required = true);

    /**
     * @brief A lookup system
     * @param exName Extension file name not the path
     * @return An extension on successful a string on error
     */
    static std::expected<NativeExtension, std::string> extensionLookUp(const std::string& exName);

    /**
     * @return Returns false of an extension has been moved or is no longer valid
     */
    [[nodiscard]] bool isValid() const;

    /**
     * @param path The full path to an extension
     */
    explicit NativeExtension(const std::string& path);

    /**
     * @return A reference to the extension entry point
     */
    [[nodiscard]]
    const ExtensionEntryPointCall_t& getExtensionEntryPointCall() const;

    /**
     * @return Returns the path to the extension
     */
    [[nodiscard]]
    const std::string& getExtensionPath() const;

    /**
     * @return the path of the extension as well
     */
    std::string toString() const override;

    /**
     * @brief A relatively safe way to look up symbols within an extension
     * @tparam T The type of the symbol you are looking up
     * @param symStr
     * @return A pointer to that symbol as T* But on error returns a string
     * @note for C++ code Please make sure that the symbol names are not mangled
     */
    template<typename T>
    std::expected<std::add_pointer_t<std::type_identity_t<T>>, std::string> extensionSymbolLookup(const std::string& symStr) const
    {
        try
        {
            //This is very spooky but trust me Bro it's this way, or it does not work
            //And yes this does break my rule of self enforced strict aliasing
            return reinterpret_cast<std::add_pointer_t<T>>(blindSymbolLookup(symStr));
        }
        catch (std::runtime_error& e)
        {
            return std::unexpected(e.what());
        }
    }

    /**
     * @return Returns a pointer to the extensions header
     */
    const lex61_header_t* getExtensionHeader() const;

    __inline const lex61_header_t& getExtensionHeaderAsRef() const
    {
        return *getExtensionHeader();
    }

    ~NativeExtension() override;
    NativeExtension(const NativeExtension& nativeExtension) = delete;
    NativeExtension(NativeExtension&& nativeExtension) noexcept;
};
}

#endif //NATIVEEXTENSION_HPP
