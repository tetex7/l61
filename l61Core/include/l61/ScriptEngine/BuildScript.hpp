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
// Created by tete on 05/01/2025.
//
#pragma once
#ifndef L61_BUILDSCRIPT_HPP
#define L61_BUILDSCRIPT_HPP

#include "l61/ScriptEngine/RunnableScriptEnvironment.hpp"
namespace l61::ScriptEngine
{

class BuildScript : public RunnableScriptEnvironment
{
protected:
    int run(const std::vector<std::string>& args) override;
    void scriptPreInit() override;
public:
    explicit BuildScript(const std::string& scriptFilePath, l61_stat& scriptCtx);
    ~BuildScript() override;
};

}

#endif //BUILDSCRIPT_HPP
