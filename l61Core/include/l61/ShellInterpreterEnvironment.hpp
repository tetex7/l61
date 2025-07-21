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
// Created by tete on 07/20/2025.
//

#ifndef L61_SHELLINTERPRETERENVIRONMENT_HPP
#define L61_SHELLINTERPRETERENVIRONMENT_HPP

#include "l61/ScriptEnvironment.hpp"
namespace l61
{

    class ShellInterpreterEnvironment : public ScriptEnvironment
    {
    protected:
        int run(const std::vector<std::string>& args) override;

        void scriptPreInit() override;

    public:
        ShellInterpreterEnvironment(const std::string& scriptFilePath, l61_stat& scriptCtx);
    };

} // l61

#endif //L61_SHELLINTERPRETERENVIRONMENT_HPP
