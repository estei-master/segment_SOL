#!/bin/bash                                          

# Author : Pierre-jean TEXIER
# Date   : November 2013
# Goal	 : write capacity of battery on /tmp/LOG

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

# Variables #
LIMIT=50

if [ $(cat /sys/class/power_supply/battery/capacity) -ge $LIMIT ]  
then
        echo "$(cat /sys/class/power_supply/battery/capacity)%" >> /tmp/LOG
else
	# On passe le governor en mode powersave (fréquence la plus basse)
	# Governor disponible sur notre SoC
	#	powersave
	#	fantasy
	#	ondemand
	#	interactive
	#	userspace
	#	perfomance

        #echo powersave > /sys/devices/system/cpu/cpu0/cpufreq/scalling_governor
        #echo powersave > /sys/devices/system/cpu/cpu1/cpufreq/scalling_governor
fi


