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
#include <stdexcept>
#include <type_traits>
#ifndef NATIVEEXTENSION_HPP
#define NATIVEEXTENSION_HPP

#include "defs.hpp"
#include <expected>

#include "l61Object.hpp"
namespace l61
{

class NativeExtension final : public l61Object
{
public:
    static constexpr const char* entryPointSymbolName = "__l61_rt_ex_init__";

    static constexpr const char* headerSymbolName = "__lex61_header__";

    using ExtensionEntryPoint_t = int(l61_api_extension_ptr);
    using ExtensionEntryPointPtr_t = std::add_pointer_t<ExtensionEntryPoint_t>;
    using ExtensionEntryPointCall_t = std::function<ExtensionEntryPoint_t>;
private:
    std::string extensionPath;
    void* soHandle;
    ExtensionEntryPointCall_t extensionEntryPointCall;

    [[nodiscard]] void* blindSymbolLookup(const std::string& symStr) const;

    void isGoodExtension() const;
public:
    static int safeExtensionLoad(const std::expected<NativeExtension, std::string>& extension, l61_api_extension_ptr api, bool required = true);
    static std::expected<NativeExtension, std::string> extensionLookUp(const std::string& exName);

    [[nodiscard]] bool isValid() const;

    explicit NativeExtension(const std::string& path);

    [[nodiscard]]
    const ExtensionEntryPointCall_t& getExtensionEntryPointCall() const;
    [[nodiscard]]
    const std::string& getExtensionPath() const;

    std::string toString() const override;

    template<typename T>
    std::expected<std::add_pointer_t<std::type_identity_t<T>>, std::string> extensionSymbolLookup(const std::string& symStr) const
    {
        try
        {
            return reinterpret_cast<std::add_pointer_t<T>>(blindSymbolLookup(symStr));
        }
        catch (std::runtime_error& e)
        {
            return std::unexpected(e.what());
        }
        
    }

    const lex61_header_t* getExtensionHeader() const;

    inline const lex61_header_t& getExtensionHeaderAsRef() const
    {
        return *getExtensionHeader();
    }

    ~NativeExtension() override;
    NativeExtension(NativeExtension& nativeExtension) = delete;
    NativeExtension(NativeExtension&& nativeExtension) noexcept;
};
}

#endif //NATIVEEXTENSION_HPP
