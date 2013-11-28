NOYAU
======


- make A20-OLinuXino_MICRO_config

- make CROSS_COMPILE=/home/$USERNAME/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf- -j2

- make ARCH=arm CROSS_COMPILE=/home/$USERNAME/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf-  sun7i_defconfig

- make ARCH=arm CROSS_COMPILE=/home/$USERNAME/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf-  xconfig

- make ARCH=arm CROSS_COMPILE=/home/$USERNAME/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf-  uImage -j2
