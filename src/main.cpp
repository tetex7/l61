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
// Created by tete on 04/27/2025.
//

#include "BuildScript.hpp"
#include "ShellScript.hpp"
#include "defs.hpp"
#include "argh.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

std::unique_ptr<ScriptEnvironment> shEnv;

std::string get_exe_str()
{
    std::unique_ptr<char[]> exe_buff = std::unique_ptr<char[]>(new char[PATH_MAX]);
    ssize_t len = readlink("/proc/self/exe", exe_buff.get(), PATH_MAX);
    std::unique_ptr<char[]> out_buff = std::unique_ptr<char[]>(new char[len+1]);
    std::strncpy(out_buff.get(), exe_buff.get(), len+1);
    return std::string(out_buff.get());
}

l61_stat mstat = {
    fs::current_path().string(),
    fs::current_path().string() + "/build.l61",
    get_exe_str(),
    std::getenv("USER"),
    std::getenv("HOME"),
    std::vector {
        (get_exe_str() + "/lib"),
        (std::string(std::getenv("HOME")) + "/l61_lib"),
        (fs::current_path().string() + "/scripts")
    },
    ProgramStatus {
        ScriptMode::UndefMode
    }
};

#define REP_BUG_TEXT "Copyright (C) 2025  Tetex7.\nFor Docs and bug reporting\nplease see: <https://github.com/tetex7/l61>."
void help(po::options_description& desc)
{
    cout_print("Usage: l61 [options] [PATH_TO_FILE]\n");
    /*cout_print("l61 HELP:\n",
        "--mode, -m, = [\"build\", \"shall\"]       : The script mode defaults to build\n",
        "--help,    -h                          : you'r reading it lol\n"
    );*/
    cout_print(desc);

    cout_print("\n\n");
    //cout_print(FV_VER, '\n');
    cout_print(REP_BUG_TEXT, '\n');
    //exit(ecode);
}

int main(int argc, const char* argv[])
{
    po::options_description desc("l61 options"s);
    desc.add_options()
    ("help,h", "produce help message")
    ("script,s", po::value<std::string>()->value_name("path"), "path to script file")
    ("mode,m", po::value<std::string>()->value_name("{\"shell\" or \"build\"}"s), "Every mode is specialized to what they're used for");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.contains("help"s))
    {
        help(desc);
        return 1;
    }

    if (vm.contains("mode"s))
    {
        mstat.procStat.runMode = toScriptMode(vm["mode"s].as<std::string>());
    }
    else
    {
        mstat.procStat.runMode = ScriptMode::BuildScriptMode;
    }

    if (vm.contains("script"s))
    {
        mstat.make_file_path = vm["script"s].as<std::string>();
    }

    if (!fs::exists(mstat.make_file_path))
    {
        std::println(std::cerr, "file {} Doesn't exists", mstat.make_file_path);
        help(desc);
        return 1;
    }

    cout_print("loading file ", mstat.make_file_path, " in ", scrModeToStr(mstat.procStat.runMode), '\n');

    switch (mstat.procStat.runMode)
    {
    case ScriptMode::BuildScriptMode:
        shEnv = std::make_unique<BuildScript>(mstat.make_file_path, mstat);
        break;
    case ScriptMode::ShellScriptMode:
        shEnv = std::make_unique<ShellScript>(mstat.make_file_path, mstat);
        break;
    default:
        shEnv = std::make_unique<BuildScript>(mstat.make_file_path, mstat);
        break;
    }

    std::vector<std::string> lua_arg_vector = {};

    for (std::size_t i = 0; i < argc; i++)
    {
        lua_arg_vector.emplace_back(argv[i]);
    }

    return shEnv->scriptRun(lua_arg_vector);
}
