#!/bin/sh

# Author : Pierre-jean TEXIER        
# Date   : November 2013 

# Copyright (C) 2013 Pierre-jean TEXIER
                                                        
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.

# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#
##############################################################################


mkdir a20_kernel_3.4_DRONE/
cd a20_kernel_3.4_DRONE/
git clone -b sunxi https://github.com/linux-sunxi/u-boot-sunxi.git
cd u-boot-sunxi/
make A20-OLinuXino_MICRO_config CROSS_COMPILE=/home/texierp/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf- -j2
cd ..
git clone https://github.com/texierp/linux-sunxi.git && cd linux-sunxi/
make sun7i_defconfig
make ARCH=arm xconfig
