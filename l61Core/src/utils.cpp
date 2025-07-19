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

#include "l61/utils.hpp"
#include <fstream>
#include <functional>
#include <iostream>
namespace l61
{

    std::vector<char> get_file(const std::string& f_name)
    {
        std::fstream file = std::fstream(f_name);
        std::vector<char> out_vet;
        char ch = 0;
        while(ch != std::fstream::traits_type::eof())
        {
            ch = file.get();
            out_vet.push_back(ch);
        }
        return out_vet;
    }

    std::string get_file_str(const std::string& f_name)
    {

        std::vector<char> out_vet = get_file(f_name);
        out_vet.push_back('\0');
        std::string out = std::string(out_vet.data());
        return out;
    }

    struct pclose_f
    {
        int operator()(FILE* __stream) const
        {
            return pclose(__stream);
        }
    };

    std::string execEx(const char* cmd)
    {
        std::array<char, PATH_MAX> buffer{};
        std::string result;
        std::unique_ptr<FILE, pclose_f> pipe(popen(cmd, "r"), pclose_f());
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }


    std::string get_input(const std::string& prompt)
    {
        if (!prompt.empty()) {
            std::cout << prompt << ' ';
        }

        std::string input;

        while (true)
        {
            const char ch = static_cast<char>(std::cin.get());
            if (ch == '\n' || ch == '\r') {
                break;
            }
            if (ch == '\b' || ch == 127) { // Handle backspace or delete
                if (!input.empty()) {
                    input.pop_back();
                    std::cout << "\b \b"; // Erase char from terminal
                }
            } else {
                input += ch;
            }
        }
        return input;
    }
}