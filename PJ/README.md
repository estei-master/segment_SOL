Pierre-Jean TEXIER
============

![ESTEI](https://github.com/estei-master/segment_SOL/blob/master/PJ/Slide/common/estei.png)

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

`Slide` 
:   Contient les slides de la présentation orale du projet (fichier Latex + Makefile)

`openCV`
:   Contient un mini tuto pour cross-compiler openCV

`Optimisation_TEMPS_DE_BOOT` 
:   Contient les images de boot, des patchs, ...

`openGLES` 
:   Contient un mini tuto pour installer le driver mali	

`power_management` 
:   Contient un script permettant de récupérer le pourcentage de niveau batterie

`uboot_kernel` 
:   Contient des scripts (bash, Makefile, ...), ainsi que le dernier .config à jour

README.md vers PDF
------------------
	su -c 'aptitude install pandoc' 
	pandoc README.md -o qt.pdf


