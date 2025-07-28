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

set -e  # Exit on error

IMAGE_NAME="l61-dev-env"
PROJECT_DIR="$(pwd)"

echo "Building Docker image: $IMAGE_NAME"
docker build -t "$IMAGE_NAME" .
#-it
echo "Running container from $IMAGE_NAME"
docker run --rm -i \
  --user builder \
  -v "$PROJECT_DIR":/home/builder/project \
  -w /home/builder/project \
  "$IMAGE_NAME" /home/builder/project/dev_setup.sh "$@"

  #-u $(id -u):$(id -g) \