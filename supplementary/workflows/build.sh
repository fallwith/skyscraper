TERMUX_PKG_HOMEPAGE=https://github.com/Gemba/skyscraper
TERMUX_PKG_DESCRIPTION="TODO"
TERMUX_PKG_LICENSE="Apache-2.0"
TERMUX_PKG_MAINTAINER="@denisidoro"
TERMUX_PKG_VERSION=4.1.0
TERMUX_PKG_REVISION=2
TERMUX_PKG_DEPENDS="qt5-qtbase"
TERMUX_PKG_BUILD_DEPENDS="qt5-qtbase-cross-tools"

termux_step_make_install() {
   export PATH="${TERMUX_PREFIX}/opt/qt/cross/bin:${PATH}"

   cd /home/builder/termux-packages/packages/buildsrc || exit 1
   pwd
   ls

   ./update_skyscraper.sh
	install -Dm755 -t "$TERMUX_PREFIX"/bin Skyscraper
}
