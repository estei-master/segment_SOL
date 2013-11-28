% Installation Driver MALI
% TEXIER Pierre-jean
% Année 2013/2014
% Master 2

Synopsis
========

Petit tutoriel permettant d'implémenter l'accélération matérielle sur l'olinuxino A20 (Mali 400MP2)

Description
===========

	Machine de dev = olinuxino A20

Préambule : 
=====
	Insertion du driver mali : modprobe mali
	Le mieux est d'écrire ceci dans '/etc/modules' : 
	ump
	mali

Préambule bis : 
=====

Téléchargement du dépot git
------------------------
	git clone https://github.com/linux-sunxi/sunxi-mali.git
	cd sunxi-mali
	git submodule init
	git submodule update

First : Compiler pour framebuffer
=====
	make config VERSION=r3p1 EGL_TYPE=framebuffer
	make 
	make install

Tester (application triangle)
=====
	cd test
	make
	./test
	



