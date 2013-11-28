# Author : Pierre-jean TEXIER	
# Date   : November 2013							
							
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


ARCH ?= arm
CROSS_COMPILE ?= /home/texierp/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf-
KERNEL_DIR ?= /home/texierp/a20_kernel_3.4_DRONE/linux-sunxi
CFLAGS := -O3 -march=armv7-a -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard

.PHONY: uImage modules help
uImage::
	@echo "Création du dossier config_`date +\%d-%m-%y_%X`"
	mkdir -p ${KERNEL_DIR}/LOG/config_`date +\%d-%m-%y_%X`
	cp -f ${KERNEL_DIR}/.config ${KERNEL_DIR}/LOG/config_`date +\%d-%m-%y_%X`/config_`date +\%d-%m-%y_%X`.txt
	${MAKE} -C ${KERNEL_DIR} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -j2 uImage

modules::
	${MAKE} -C ${KERNEL_DIR} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -j2 INSTALL_MOD_PATH=output modules
	${MAKE} -C ${KERNEL_DIR} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -j2 INSTALL_MOD_PATH=output modules_install

help::
	@echo "\n\tMakefile permettant de générer l'image kernel"
	@echo "\n"
