Options de compilations
====

`-mfloat-abi` 
:   Spécifie l'ABI à utiliser pour l'unité de virgule flottante (soft / hard / softfp) --> `hard` 

`-mtune` 
:   Précise à GCC d'optimiser le code pour l'architecture choisie --> `cortex-a7` 

`-mfpu` 
:   Définie l'unité de virgule flottante disponible sur la carte --> `neon-vfvp4` 

`-mcpu` 
:   Ceci spécifie le nom du processeur cible ARM. GCC utilise ce nom pour déterminer le type d'instructions, il peut émettre lors de la génération du code assembleur. --> `cortex-a7` 


Pour plus d'informations :
-------------------------

      http://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
