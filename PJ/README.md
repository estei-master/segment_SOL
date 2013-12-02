Pierre-Jean TEXIER
============

TODO
----

- Création de l'OS Linux minimaliste (Bootloader, kernel, RootFS)
- Cross compilation de Qtembedded et tslib
- Cross Compilation de openCV
- Gestion du power management

Hiérarchie des dossiers
----------------------
`Qt` 
:   Contient un mini tuto pour cross-compiler Qt embedded, des exemples, des tests, ...

`openCV`
:   Contient un mini tuto pour cross-compiler openCV	

`openGLES` 
:   Contient un mini tuto pour installer le driver mali	

`uboot&kernel` 
:   Contient des scripts (bash, Makefile, ...), ainsi que le dernier .config à jour

README.md vers PDF
------------------
	su -c 'aptitude install pandoc' 
	pandoc README.md -o qt.pdf


