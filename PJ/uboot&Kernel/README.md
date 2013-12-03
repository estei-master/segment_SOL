Bootloader & Kernel
============

Hiérarchie des dossiers
----------------------
`config` 
:   Contient le dernier .config à jour

`a20_kernel_3.4_DRONE`
:   Contient:
	linux-sunxi : Contient un ensemble de fichiers permettant de générer l'image kernel : fork du projet sunxi
	uboot-sunxi : Contient un ensemble de fichiers permettant de générer le bootloader : fork du projet sunxi
	Makefile : Permet de générer : le bootloader, une image kernel ou les modules kernel

