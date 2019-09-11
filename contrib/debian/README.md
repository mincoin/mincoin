
Debian
====================
This directory contains files used to package mincoind/mincoin-qt
for Debian-based Linux systems. If you compile mincoind/mincoin-qt yourself, there are some useful files here.

## mincoin: URI support ##


mincoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mincoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mincoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/mincoin128.png` to `/usr/share/pixmaps`

mincoin-qt.protocol (KDE)

