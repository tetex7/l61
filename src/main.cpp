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
#include <memory>
#include <print>
#include <readline/readline.h>
#include <csignal>
#include <string>

#include "BuildScript.hpp"
#include "ShellScript.hpp"
#include "defs.hpp"

#include "ExtensionManager.hpp"
#include "Logger.hpp"
#include "NativeExtension.hpp"
#include "utils.hpp"
#include "AbstractScriptDebugger.hpp"


namespace po = boost::program_options;

namespace l61
{
std::unique_ptr<ScriptEnvironment> shEnv;
std::unique_ptr<AbstractScriptDebugger> luaDugger;


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
        0,
        {},
        EventBus()
    }
};
}

//using namespace l61;

l61::config_t mkConfig()
{
    return {
        {},
        {}
    };
}



#define REP_BUG_TEXT "Copyright (C) 2025  Tetex7.\nFor Docs and bug reporting\nplease see: <https://github.com/tetex7/l61>."
static void help(po::options_description& desc)
{
    l61::cout_print("Usage: l61 [options] [PATH_TO_FILE]\n");
    l61::cout_print(desc);
    l61::cout_print("\n\n");
    l61::cout_print("version: ", l61::mstat.version, '\n');
    l61::cout_print(REP_BUG_TEXT, '\n');
}

l61::l61_api_extension_t exdata = {
    l61::mstat,
    l61::shEnv
};


static void sighandler_f(int sig)
{
    l61::mstat.procStat.signalStack.push(sig);
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
        l61::mstat.procStat.verbose = 1;
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
            l61::mstat.spaths.push_back(path);
        }
    }

    if (vm.contains("cd"s))
    {
        l61::mstat.work_path = vm["cd"s].as<std::string>();
        l61::mstat.make_file_path = l61::mstat.work_path + "/build.l61";
        l61::mstat.spaths[2] = l61::mstat.work_path + "/scripts";
    }

    if (vm.contains("mode"s))
    {
        l61::mstat.procStat.runMode = l61::toScriptMode(vm["mode"s].as<std::string>());
    }
    else
    {
        l61::mstat.procStat.runMode = l61::ScriptMode::BuildScriptMode;
    }

    if (vm.contains("spaths"s))
    {
        for (std::size_t i = 0; i < l61::mstat.spaths.size(); i++)
        {
            l61::cout_print("[", i, "] = \"", l61::mstat.spaths[i] + "\"\n");
        }
        return 0;
    }

    if (vm.contains("script"s))
    {
        l61::mstat.make_file_path = vm["script"s].as<std::string>();
    }

    std::signal(SIGINT, &sighandler_f);

    if (!fs::exists(l61::mstat.make_file_path))
    {
        std::println(std::cerr, "file {} Doesn't exists", l61::mstat.make_file_path);
        help(desc);
        return 1;
    }


    l61::mstat.procStat.eventBus.addEvent(SIGINT, []() -> void {
        l61::toLogger(l61::LogLevel::FATAL, "SIGINT detected goodbye");
        std::exit(0);
    });

    switch (l61::mstat.procStat.runMode)
    {
    case l61::ScriptMode::BuildScriptMode:
        l61::shEnv = std::make_unique<l61::BuildScript>(l61::mstat.make_file_path, l61::mstat);
        l61::NativeExtension::safeExtensionLoad(l61::NativeExtension::extensionLookUp("build.lex61"s), &exdata, false);
        break;
    case l61::ScriptMode::ShellScriptMode:
        l61::shEnv = std::make_unique<l61::ShellScript>(l61::mstat.make_file_path, l61::mstat);
        l61::NativeExtension::safeExtensionLoad(l61::NativeExtension::extensionLookUp("script.lex61"s), &exdata, false);
        break;
    default:
        l61::shEnv = std::make_unique<l61::BuildScript>(l61::mstat.make_file_path, l61::mstat);
        break;
    }

    l61::toLogger(l61::LogLevel::INFO, "loaded file {} in {}", static_cast<std::string>(*l61::shEnv), l61::scrModeToStr(l61::mstat.procStat.runMode));

    std::vector<std::string> lua_arg_vector = {};

    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); i++)
    {
        lua_arg_vector.emplace_back(argv[i]);
    }

    //NativeExtension::safeExtensionLoad(NativeExtension::extensionLookUp("base.lex61"s), &exdata, false);
    l61::mstat.procStat.extension_manager->lookupAndLoadExtension("base.lex61", &exdata);

    l61::shEnv->addValue("spaths"s, l61::mstat.spaths);

    l61::shEnv->specialRun([](sol::state& lua) {
        lua_State* L = lua.lua_state();
        lua_sethook(L, l61::lambdaToFunPtr<std::remove_pointer_t<lua_Hook>>([](lua_State* L, lua_Debug* D) -> void {
            //This event handler and message pump is work in progress
            //why is it hooked into the lua environment you might ask
            //Because when Lua Code is running I do not have control over the environment
            //and this is a hack that I thought up many nights
            //This should not influence the lua environment
            //Yes exists, so I can have code time to run my event system
            //TODO: Move this to a separate function

            (void)L; // This is done to appease the compiler(-Werror)
            (void)D; // Learn this trick from NASA Documentation of all places

            if (!l61::mstat.procStat.signalStack.empty())
            {
                l61::c_signal_t sig = l61::mstat.procStat.signalStack.front();
                l61::mstat.procStat.signalStack.pop();
                l61::mstat.procStat.eventBus.push(sig);
            }
            l61::mstat.procStat.eventBus.pumpIt();
        }), LUA_MASKCOUNT, 50);
    });

    return l61::shEnv->scriptRun(lua_arg_vector);
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
        l61::toLogger(l61::LogLevel::FATAL, "{}", e.what());
        //std::println(std::cerr, "error: {}", e.what());
        exit(1);
    }
}
