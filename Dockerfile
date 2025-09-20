#
# Copyright (C) 2025  Tetex7
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

FROM archlinux:latest
LABEL authors="Tetex7"

ARG USER_ID=1000
ARG GROUP_ID=1000

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm --needed \
    base-devel cmake gcc ninja git lua readline boost boost-libs gtest doxygen abseil-cpp
RUN pacman -Scc --noconfirm

# Create non-root user
RUN groupadd -g $GROUP_ID builder \
 && useradd -m -u $USER_ID -g $GROUP_ID -s /bin/bash builder
USER builder
WORKDIR /home/builder/project