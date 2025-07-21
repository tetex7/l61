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
#include <stacktrace>


#include "l61/ShellScript.hpp"
#include "l61/ShellInterpreterEnvironment.hpp"
#include "l61/defs.hpp"
#include "l61/l61_config.h"

#include "l61/ExtensionManager.hpp"
#include "l61/Logger.hpp"
#include "l61/NativeExtension.hpp"
#include "l61/utils.hpp"
#include "l61/AbstractScriptDebugger.hpp"
#include "l61/IBasicScriptEngine.hpp"


namespace po = boost::program_options;

namespace l61
{
    std::unique_ptr<AbstractScriptDebugger> luaDugger;


    l61_stat mstat = {
        fs::current_path().string(),
        fs::current_path().string() + "/script.l61",
        fs::read_symlink("/proc/self/exe"),
        std::getenv("USER"),
        std::getenv("HOME"),
        std::vector {
            (fs::read_symlink("/proc/self/exe").parent_path().parent_path().string() + "/lib"),
            (std::string(std::getenv("HOME")) + "/.l61_lib"),
            (fs::current_path().string())
        },
        L61_CONFIG_STR_VERSION,
        ProgramStatus {
            ScriptMode::ShellScriptMode,
            std::make_unique<ExtensionManager>(),
            {},
            0,
            {},
            EventBus()
        }
    };

    std::unique_ptr<ScriptEnvironment> shEnv = std::make_unique<ShellInterpreterEnvironment>("", mstat);
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
    l61::cout_print("Usage: sh61 [options] [PATH_TO_FILE]\n");
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
    ("cd,C", po::value<std::string>()->value_name("path"s), "Falsifies the current directory")
    ("spaths,", "Dumps the built-in spaths")
    ("add-to-spaths,p", po::value<std::vector<std::string>>()->composing()->value_name("path"), "Add values to the spaths")
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
        l61::mstat.make_file_path = l61::mstat.work_path + "/script.l61";
        l61::mstat.spaths[3] = l61::mstat.work_path;
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
    std::signal(SIGTERM, &sighandler_f);

    /*if (!fs::exists(l61::mstat.make_file_path))
    {
        std::println(std::cerr, "file {} Doesn't exists", l61::mstat.make_file_path);
        help(desc);
        return 1;
    }*/


    l61::mstat.procStat.eventBus.addEvent(SIGINT, []() -> void {
        std::string input = l61::get_input("\nexit(y/n):");
        if (input == "yes" || input == "y") std::exit(0);
    });

    l61::mstat.procStat.eventBus.addEvent("com.trs.l61.debugger_initialization", [](){});

    std::vector<std::string> lua_arg_vector = l61::null;

    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); i++)
    {
        lua_arg_vector.emplace_back(argv[i]);
    }

    //NativeExtension::safeExtensionLoad(NativeExtension::extensionLookUp("base.lex61"s), &exdata, false);
    auto& base_ex = l61::mstat.procStat.extension_manager->lookupAndLoadExtension("base.lex61", l61::null, false);

    int base_ret = base_ex.getExtensionEntryPointCall()(&exdata);
    if (base_ret) throw std::runtime_error(std::format("Entry point for extension base.lex16 Returned A value of {}", base_ret));

    l61::shEnv->addValue("spaths"s, l61::mstat.spaths);

    l61::mstat.procStat.eventBus.push("com.trs.l61.PreLuaBoot");

    l61::shEnv->specialRun([](const sol::state& lua) {
        lua_State* L = lua.lua_state();
        lua_sethook(L, l61::lambdaToFunPtr<std::remove_pointer_t<lua_Hook>>([](l61_unused lua_State* L, l61_unused lua_Debug* D) -> void {
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
        }), LUA_MASKCOUNT, 1);
    });

    while (true)
    {
        std::string inp = readline("lua>");
        l61::shEnv->exec(inp);
    }

    return 0;
}


/**
 * @brief A slim main for exception handling
 * @param argc Number of arguments
 * @param argv A pointer to the array of arguments
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
        l61::toLogger(l61::LogLevel::FATAL, "Unhandled exception: {}", e.what());
        std::exit(1);
    }
}
