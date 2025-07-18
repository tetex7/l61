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
pkgdesc=''
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
    DEBUG=${PK_DEBUG} RVER=${pkgver} ./full_build.sh
}

package() {
    cd ..
    echo $PWD
    mkdir "${pkgdir}/opt"
    ./package.sh
    cp -rv ./l61-*-pak "${pkgdir}/opt/l61"

    mkdir -p "${pkgdir}/etc/profile.d"
    cat >> "${pkgdir}/etc/profile.d/l61.sh" <<_ACEOF
append_path '/opt/l61/bin'
export PATH
_ACEOF
    chmod +X "${pkgdir}/etc/profile.d/l61.sh"
}
