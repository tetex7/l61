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
// Created by tete on 09/15/2025.
//

#include "l61/RosettaSystem/getExecutablePath.hpp"
#include <string>
#include <stdexcept>


#if defined(_WIN32)
#include <windows.h>
#elif defined(__OpenBSD__)
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <limits.h>
#elif defined(__FreeBSD__) || defined(__DragonFly__)
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <limits.h>
#endif

namespace l61::RosettaSystem
{
    std::filesystem::path getExecutablePath()
    {
#if defined(_WIN32)
        char buf[MAX_PATH];
        DWORD len = GetModuleFileNameA(nullptr, buf, MAX_PATH);
        if (len == 0 || len == MAX_PATH)
        {
            throw std::runtime_error("Failed to get executable path on Windows");
        }
        return std::filesystem::canonical(std::string(buf, len));
#elif defined(__linux__)
        return std::filesystem::read_symlink("/proc/self/exe");
#elif defined(__OpenBSD__)
        int mib[4];
        char buf[PATH_MAX];
        size_t len = sizeof(buf);

        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC_ARGS;
        mib[2] = getpid();
        mib[3] = KERN_PROC_PATHNAME;

        if (sysctl(mib, 4, buf, &len, nullptr, 0) == 0)
        {
            return std::filesystem::path(std::string(buf, len - 1));
        }
        else
        {
            throw std::runtime_error("Failed to get executable path on OpenBSD");
        }

#elif defined(__FreeBSD__) || defined(__DragonFly__)
        int mib[4];
        char buf[PATH_MAX];
        size_t len = sizeof(buf);

        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PATHNAME;
        mib[3] = getpid();

        if (sysctl(mib, 4, buf, &len, nullptr, 0) == 0)
        {
            return std::filesystem::path(std::string(buf, len - 1));
        }
        else
        {
            throw std::runtime_error("Failed to get executable path on FreeBSD/DragonFly");
        }
#elif defined(__APPLE__)
        char buf[PATH_MAX];
        uint32_t size = sizeof(buf);

        if (_NSGetExecutablePath(buf, &size) == 0)
        {
            return std::filesystem::canonical(buf);
        }
        else
        {
            throw std::runtime_error("Buffer too small for executable path on macOS");
        }
#else
#  error "getExecutablePath is not implemented for this platform"
#endif
    }
}


