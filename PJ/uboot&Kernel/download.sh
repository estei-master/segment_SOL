#!/bin/sh

#  download.sh
#  
#
#  Created by Pierre-jean Texier on 07/11/13.
#


mkdir a20_kernel_3.4_DRONE/
cd a20_kernel_3.4_DRONE/
git clone -b sunxi https://github.com/linux-sunxi/u-boot-sunxi.git
cd u-boot-sunxi/
make A20-OLinuXino_MICRO_config CROSS_COMPILE=/home/texierp/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf- -j2
cd ..
git clone https://github.com/texierp/linux-sunxi.git && cd linux-sunxi/
make sun7i_defconfig
make ARCH=arm xconfig
