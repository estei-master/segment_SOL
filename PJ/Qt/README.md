% Qt embedded notice d'utilisation
% TEXIER Pierre-jean
% Année 2013/2014
% Master 2

Synopsis
========

Petit tutoriel permettant d'implémenter Qt embedded sur plateforme ARM (Olinuxino A20)

Description
===========

	Machine de dev = debian 64 bits

Using `Qt embedded` version 4.8.2
--------------

Préambule : L'environnement 
=====

	pkg-config
	libqt4-dev
	gettext
	automake
	libtool
	bison
	gawk
	flex
	gperf
	build-essential
	ibncurses5-dev
	libc6-i386
	lib32stdc++6
	lib32z1
	
	su -c 'aptitude -y install pkg-config libqt4-dev gettext automake libtool bison gawk flex gperf build-essential libncurses5-dev libc6-i386 lib32stdc++6 lib32z1'


Préambule bis : Le cross-compilateur (de chez Linaro)
=====

Téléchargement via git --> commande : 
------------------------
	git clone https://github.com/texierp/PROJET_Drone.git
	<chemin de la cross-tool chain>=
	PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux

First : Compiler tslib (en root)
=====

	Exporter dans la variable path le compilateur : 

	export PATH="${PATH}:<chemin de la cross-tool chain>/bin"

Télécharger les sources
------------------------

	root@debian:/home/texierp# git clone http://github.com/kergoth/tslib.git
	root@debian:/home/texierp# cd tslib/

Installer dh-autoreconf
------------------------

	aptitude install dh-autoreconf

DO_COMPILE()
------------------------

	root@debian:/home/texierp/tslib# ./autogen-clean.sh && ./autogen.sh
	root@debian:/home/texierp/tslib# 
	./configure \
	--host=arm-linux-gnueabihf \
	--prefix=/usr/local/tslib \
	--enable-static \
	--enable-shared
	root@debian:/home/texierp/tslib# make -j2
	root@debian:/home/texierp/tslib# make install


Second : Compiler Qtembedded (en root)
=====

	root@debian:/home/texierp/qt-everywhere# wget \
	http://download.qt-project.org/archive/qt/4.8/4.8.2/qt-everywhere-opensource-src-4.8.2.tar.gz
	root@debian:/home/texierp/qt-everywhere# tar xzvf \
	qt-everywhere-opensource-src-4.7.3.tar.gz

modification du fichier : qmake.conf
------------------------

	root@debian:/home/texierp/qt-everywhere# cd qt-everywhere-opensource-src-4.8.2

	root@debian:/home/texierp/qt-everywhere/qt-everywhere-opensource-src-4.8.2# 
	vim mkspecs/qws/linux-arm-g++/qmake.conf
			
	Il faut donc modifier le fichier comme ci-dessous : 
	
	#
	# qmake configuration for building with arm-linux-g++
	#

	include(../../common/linux.conf)
	include(../../common/gcc-base-unix.conf)
	include(../../common/g++-unix.conf)
	include(../../common/qws.conf)

	# modifications to g++.conf
	# QMAKE_CFLAGS_RELEASE    = -O3 -march=armv7-a -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=neon
	# QMAKE_CXXFLAGS_RELEASE  = -O3 -march=armv7-a -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=neon
	QMAKE_CC                = <chemin de la cross-tool chain>/bin/arm-linux gnueabihf-gcc
	QMAKE_CXX               = <chemin de la cross-tool chain>/bin/arm-linux-gnueabihf-g++
	QMAKE_LINK              = <chemin de la cross-tool chain>/bin/arm-linux-gnueabihf-g++
	QMAKE_LINK_SHLIB        = <chemin de la cross-tool chain>/bin/arm-linux-gnueabihf-g++
	
	# modifications to linux.conf
	QMAKE_AR                = <chemin de la cross-tool chain>/bin/arm-linux-gnueabihf-ar cqs
	QMAKE_OBJCOPY           = <chemin de la cross-tool chain>/bin/arm-linux-gnueabihf-objcopy
	QMAKE_STRIP             = <chemin de la cross-tool chain>/bin/arm-linux-gnueabihf-strip

	QMAKE_INCDIR += /usr/local/tslib/include
	QMAKE_LIBDIR += /usr/local/tslib/lib
	QMAKE_LFLAGS += -Wl,-rpath-link=/usr/local/tslib/lib


	load(qt_config)

DO_COMPILE()
------------------------

	root@debian:/home/texierp/qt-everywhere/qt-everywhere-opensource-src-4.8.2# 
	./configure  \
	-xplatform qws/linux-arm-g++  \
	-embedded arm  \
	-prefix /usr/local/Qt  \
	-qt-kbd-linuxinput \
	-qt-mouse-tslib  \
	-little-endian  \
	-opensource  \
	-confirm-license  \
	-I /usr/local/tslib/include/  \
	-L /usr/local/tslib/lib/  \
	-no-qt3support  \
	-no-cups  \
	-no-webkit  \
	-no-phonon  \
	-no-openssl 

	root@debian:/home/texierp/qt-everywhere/qt-everywhere-opensource-src-4.8.2# make -j2
	root@debian:/home/texierp/qt-everywhere/qt-everywhere-opensource-src-4.8.2# make install

General options
---------------

`-embedded`
:   Active la compilation pour Architecture arm

`-xplatform`
:   Cela permet de choisir l'architecture cible pour la cross-compilation

`-prefix`
:   Endroit spécifique pour l'installation

`-opensource`
:   Choisie automatiquement la version opensource

`-qt-kbd-linuxinput`
:   Active le driver clavier

`-qt-mouse-tslib`
:   Active le driver tslib(écran tactile)

`-confirm-license `
:   Permet de répondre 'yes' de façon automatique

`-I /usr/local/tslib/include/`
:   Chemin des includes de la tslib

`-L /usr/local/lib/ `
:   Chemin des librairies de la tslib

`-no-qt3support`
:   Pas de support Qt3

`-no-cups`
:   Pas de support cups

`-no-webkit`
:   Pas de support webkit

`-no-phonon`
:   Pas de support phonon

`-no-openssl`
:   Pas de support openssl

/usr/local/tslib/etc/ts.conf
------------------------

	décommenter module_raw input	

Copie des librairies
------------------------

	scp - r /usr/local/Qt root@adresse:/usr/local
	scp - r /usr/local/tslib root@adresse:/usr/local

Sur la plateforme de DEV (/etc/environment)
------------------------

	export LD_LIBRARY_PATH=/usr/local/Qt/lib:/usr/local/tslib/lib:/usr/lib
	export TSLIB_TSEVENTTYPE=raw
	export TSLIB_CONSOLEDEVICE=none
	export TSLIB_FBDEVICE=/dev/fb0
	export TSLIB_TSDEVICE=/dev/input/event0
	export TSLIB_CALIBFILE=
	export TSLIB_CONFFILE=/usr/local/tslib/etc/ts.conf
	export TSLIB_PLUGINDIR=/usr/local/tslib/lib/ts
	export QWS_MOUSE_PROTO=tslib:/dev/input/event0
	export QWS_SIZE=1024x600
	export QWS_DISPLAY="LinuxFb:mmWidth=222:mmHeight=125"
	
	Calibration
	
	/usr/local/bin/ts_calibrate /usr/local/tslib/etc/ts.calib
	export TSLIB_CALIBFILE=/usr/local/tslib/etc/ts.calib

	
TEST !!
======

	cd /usr/local/Qt/demos/embedded/lightmaps
	./lightmaps -qws

Pour compiler un programme
=====

	export PATH=/usr/local/Qt/bin:$PATH
	/usr/local/Qt/bin/qmake -spec qws/linux-arm-g++
	make
