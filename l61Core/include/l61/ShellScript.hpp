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

#ifndef L61_SHELLSCRIPT_HPP
#define L61_SHELLSCRIPT_HPP

#include "sol/sol.hpp"
#include "l61/ScriptEnvironment.hpp"
namespace l61
{

class ShellScript : public ScriptEnvironment
{
protected:
    int run(const std::vector<std::string>& args) override;

    void scriptPreInit() override;

public:
    ShellScript(const std::string& scriptFilePath, l61_stat& scriptCtx);
    ~ShellScript() override;
};


__inline sol::table makeSubTable(const std::string&& name, sol::table table)
{
    sol::table x = table.create_with();
	table.set(std::forward<const std::string>(name), x);
	return x;
}
}


#endif //SHELLSCRIPT_HPP
