#
#Copyright (C) 2024  tete
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

# Maintainer: tete <tetex7@outlook.com>
pkgname=l61
pkgver=1.0.0
pkgrel=1
pkgdesc='Passive garbage collector for C and C++'
url='www.github.com/tetex7/l61'
provides=("l61" "sh61")
arch=('x86_64')
#PACKAGER="TRS"
license=('GPL3')
makedepends=()
depends=('glibc')
options=('!strip' 'docs' 'libtool' 'staticlibs' 'emptydirs' 'zipman' '!purge' '!debug' '!lto')

prepare() {
    cd ..
    echo $PWD
    ./full_build.sh clean
}

build () {
    cd ..
    echo $PWD
    make DEBUG=1 RVER=${pkgver}
    ./full_build.sh
}

package() {
    cd ..
    minverN=$(echo "${pkgver}" | head -c 1)
    eminverN=$(echo "${pkgver}" | head -c 3)
    mkdir -p "${pkgdir}/opt/l61"
    cp -rv ./deploymentFileSystem "${pkgdir}/opt/l61"
    install -Dm755 ./build/l61.out "${pkgdir}/opt/l61/bin/l61"
    mkdir -p "${pkgdir}/opt/l61/lib/native"

}
