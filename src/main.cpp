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


#include <boost/program_options.hpp>
#include <cstdlib>
#include <filesystem>
#include <iterator>
#include <print>
#include <readline/readline.h>
#include <array>
#include <csignal>
#include <string>

#include "BuildScript.hpp"
#include "ShellScript.hpp"
#include "defs.hpp"

#include "ExtensionManager.hpp"
#include "Logger.hpp"
#include "NativeExtension.hpp"
#include "utils.hpp"


namespace po = boost::program_options;

namespace l61
{
std::unique_ptr<ScriptEnvironment> shEnv;


l61_stat mstat = {
    fs::current_path().string(),
    fs::current_path().string() + "/build.l61",
    fs::read_symlink("/proc/self/exe"),
    std::getenv("USER"),
    std::getenv("HOME"),
    std::vector {
        (fs::read_symlink("/proc/self/exe").parent_path().parent_path().string() + "/lib"),
        (std::string(std::getenv("HOME")) + "/l61_lib"),
        (fs::current_path().string() + "/scripts")
    },
    __L61__FV_VER__,
    ProgramStatus {
        ScriptMode::UndefMode,
        std::make_unique<ExtensionManager>(),
        {},
        0
    }
};
}

using namespace l61;

config_t mkConfig()
{
    return {
        {},
        {}
    };
}



#define REP_BUG_TEXT "Copyright (C) 2025  Tetex7.\nFor Docs and bug reporting\nplease see: <https://github.com/tetex7/l61>."
static void help(po::options_description& desc)
{
    cout_print("Usage: l61 [options] [PATH_TO_FILE]\n");
    cout_print(desc);
    cout_print("\n\n");
    cout_print("version: ", mstat.version, '\n');
    cout_print(REP_BUG_TEXT, '\n');
}

l61_api_extension_t exdata = {
    mstat,
    shEnv
};


static void sighandler_f(int sig)
{
    switch (sig)
    {
    case SIGINT:
        {
            std::string sg = readline("exit?(yes/no): ");
            if (sg == "yes" || sg == "y")
            {
                std::exit(0);
            }
            break;
        }
    };
}

static int l61_main(int argc, const char* argv[])
{
    po::options_description desc("l61 options"s);
    desc.add_options()
    ("help,h", "produce help message")
    ("script,s", po::value<std::string>()->value_name("path"s), "path to script file")
    ("mode,m", po::value<std::string>()->value_name(R"({"shell" or "build"})"s), "Every mode is specialized to what they're used for")
    ("cd,C", po::value<std::string>()->value_name("path"s), "Falsifies the current directory")
    ("spaths,", "Dumps the built-in spaths")
    ("add-to-spaths,p", po::value<std::vector<std::string>>()->composing(), "Add values to the spaths")
    ("verbose,v", "more loging");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.contains("verbose"s))
    {
        mstat.procStat.verbose = 1;
    }

    if (vm.contains("help"s))
    {
        help(desc);
        return 0;
    }

    if (vm.contains("add-to-spaths"s))
    {
        for (const std::string& path : vm["add-to-spaths"s].as<std::vector<std::string>>())
        {
            mstat.spaths.push_back(path);
        }
    }

    if (vm.contains("cd"s))
    {
        mstat.work_path = vm["cd"s].as<std::string>();
        mstat.make_file_path = mstat.work_path + "/build.l61";
        mstat.spaths[2] = mstat.work_path + "/scripts";
    }

    if (vm.contains("mode"s))
    {
        mstat.procStat.runMode = toScriptMode(vm["mode"s].as<std::string>());
    }
    else
    {
        mstat.procStat.runMode = ScriptMode::BuildScriptMode;
    }

    if (vm.contains("spaths"s))
    {
        for (std::size_t i = 0; i < mstat.spaths.size(); i++)
        {
            cout_print("[", i, "] = \"", mstat.spaths[i] + "\"\n");
        }
        return 0;
    }

    if (vm.contains("script"s))
    {
        mstat.make_file_path = vm["script"s].as<std::string>();
    }
    //std::println("{}", execEx("ls --help"));
    rl_initialize();

    /*rl_bind_key(':', lambdaToFunPtr<rl_command_func_t>([](int, int) -> int {
        std::println("dd");
        std::exit(2);
        return 0;
    }));*/

    std::signal(SIGINT, &sighandler_f);

    if (!fs::exists(mstat.make_file_path))
    {
        std::println(std::cerr, "file {} Doesn't exists", mstat.make_file_path);
        help(desc);
        return 1;
    }

    toLogger(LogLevel::INFO, "loading file {} in {}", mstat.make_file_path, scrModeToStr(mstat.procStat.runMode));

    switch (mstat.procStat.runMode)
    {
    case ScriptMode::BuildScriptMode:
        shEnv = std::make_unique<BuildScript>(mstat.make_file_path, mstat);
        NativeExtension::safeExtensionLoad(NativeExtension::extensionLookUp("build.lex61"s), &exdata, false);
        break;
    case ScriptMode::ShellScriptMode:
        shEnv = std::make_unique<ShellScript>(mstat.make_file_path, mstat);
        NativeExtension::safeExtensionLoad(NativeExtension::extensionLookUp("script.lex61"s), &exdata, false);
        break;
    default:
        shEnv = std::make_unique<BuildScript>(mstat.make_file_path, mstat);
        break;
    }

    std::vector<std::string> lua_arg_vector = {};

    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); i++)
    {
        lua_arg_vector.emplace_back(argv[i]);
    }

    //NativeExtension::safeExtensionLoad(NativeExtension::extensionLookUp("base.lex61"s), &exdata, false);
    mstat.procStat.extension_manager->lookupAndLoadExtension("base.lex61", &exdata);

    shEnv->addValue("spaths"s, mstat.spaths);

    return shEnv->scriptRun(lua_arg_vector);
}


/**
 * @brief A slim main for exception handling
 * @param argc Number of arguments
 * @param argv A pointer to the ray of arguments
 * @return Exit code
 */
int main(int argc, const char* argv[])
{
    try
    {
        return l61_main(argc, argv);
    }
    catch (std::exception& e)
    {
        toLogger(LogLevel::FATAL, "{}", e.what());
        //std::println(std::cerr, "error: {}", e.what());
        exit(1);
    }
}
