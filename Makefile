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
GCCFLAG = -Wall -Wextra -fno-strict-aliasing -DSOL_ALL_SAFETIES_ON  # -fPIC for Position Independent Code

ifeq ($(DEBUG),1)
  GCCFLAGS += -g -O0
else
  GCCFLAGS += -O2
endif

CFLAGS = ${GCCFLAG} -std=gnu99
CPPFLAGS = ${GCCFLAG} -std=gnu++23
LDFLAGS =  # Link as a shared object
LDLIBS = -llua -lreadline -lboost_program_options




# Directories
SRC_DIR = src
BIN_DIR = build
OBJ_DIR = ${BIN_DIR}
INCLUDE_DIR = ./include

# Source files and object files
C_SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
CPP_SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files for C and C++ sources
C_OBJ_FILES = $(C_SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.c.o)
CPP_OBJ_FILES = $(CPP_SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.cpp.o)

# All object files
OBJ_FILES = $(C_OBJ_FILES) $(CPP_OBJ_FILES)
TARGET = $(BIN_DIR)/l61.out

# Default rule: build the target
all: $(TARGET)

# Rule to link object files into the shared library
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $(OBJ_FILES) -o $(TARGET) $(LDLIBS)

# Rule to compile source files into object files
$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $(OBJ_DIR)/$*.c.o

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $(OBJ_DIR)/$*.cpp.o

# Rule for cleaning up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rule to remove only object files
clean-obj:
	rm -rf $(OBJ_DIR)/*.c.o

# Rule to remove only the shared library
clean-bin:
	rm -rf $(BIN_DIR)/$(notdir $(TARGET))

# Rule to build and run tests (if you add tests in the future)
test: $(TARGET)
	./$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean clean-obj clean-bin test