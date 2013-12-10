#!/bin/bash                                          

# Author : Pierre-jean TEXIER
# Date   : December 2013

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

echo q | fbvis /home/PJ/PBIT.png
sleep 5
if [ $(cat /sys/class/power_supply/battery/capacity) -ge $LIMIT ]  
then
        echo q | fbvis /home/PJ/PBIT_OK.png
	cd /home
	sleep 2
	./horizon.sh
else
	echo q | fbvis /home/PJ/PBIT_Failed.png
fi


