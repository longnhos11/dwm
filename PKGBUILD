# Maintainer: longnhos11<longnhos11@gmail.com>
pkgname=dwm
pkgver=6.4
pkgrel=1
pkgdesc="dwm build for phyOS"
arch=(x86_64)
url="git://github.com/longnhos11/dwm"
license=('MIT')
depends=('libxcb' 'libxft-bgra' 'imlib2' 'libconfig')
makedepends=('git' 'make')
optdepends=('fonts-phyOS' 'dmenu-phyOS' 'st-phyOS' 'dwmblocks-phyOS')
provides=("dwm")
conflicts=("dwm")
options=('zipman')
source=('git+https://github.com/longnhos11/dwm')
md5sums=('SKIP')

build() {
	cd "$pkgname"
	[ -f "$HOME/.config/phyos/dwm/keys.h" ] && yes | cp -f "$HOME/.config/phyos/dwm/keys.h" ./keys.h
	make
}

package() {
	cd "$pkgname"
	make PREFIX=/usr DESTDIR="$pkgdir/" install
}
