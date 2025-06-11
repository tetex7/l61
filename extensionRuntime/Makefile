#
# Copyright (C) 2025  tetex7
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

DEBUG ?= 1

# Compiler and flags
CC = gcc
CXX = g++
AR = ar
GCCFLAG = -fPIC -rdynamic -Wall -Wextra -fno-strict-aliasing -DSOL_ALL_SAFETIES_ON -include l61/PseudoKeywords.hpp  # -fPIC for Position Independent Code

ifeq ($(DEBUG),1)
  GCCFLAGS += -g -O0
else
  GCCFLAGS += -O2
endif

CFLAGS = ${GCCFLAG} -std=gnu99
CPPFLAGS = ${GCCFLAG} -std=gnu++23

SRC_DIR = src

INCLUDE_DIR = -I./include -I../include

RT_OBJ = l61_extension_rt.o

$(RT_OBJ): rt_main.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDE_DIR) -c $< -o $(RT_OBJ)

# Rule for cleaning up build artifacts
clean:
	rm -f ./${RT_OBJ}
# Phony targets (not actual files)
.PHONY: all clean clean-obj clean-bin test