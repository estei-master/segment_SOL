#!/bin/bash                                          

# Author : Pierre-jean TEXIER
# Date   : November 2013

# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.

# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.

# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#--------------------------------------------------------------------------------#

# Variables #
LIMIT=50

if [ $(cat /sys/class/power_supply/battery/capacity) -ge $LIMIT ]  
then
        echo "`date +\%d-%m-%y_%X` : $(cat /sys/class/power_supply/battery/capacity)%" >> /tmp/LOG_pm
else
        echo "Niveau de charge Batterie inférieur à $LIMIT%"
        #echo powersave > /sys/devices/system/cpu/cpu0/cpufreq/scalling_governor
        #echo powersave > /sys/devices/system/cpu/cpu0/cpufreq/scalling_governor
        kill -9 $(pidof lightmaps)
fi
