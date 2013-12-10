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
NAME='power_management.png'

echo "set terminal png size 1024,600 ; set xrange [0:40] ; set xlabel 'Temps' ; set ylabel '% Batterie' ; set title 'Consommation Batterie sur 34 min' ; set output './$NAME'; set multiplot layout 2,1 ;
	plot '$1' using 1:2 with linespoints title 'Sans Appli Qt'  ; 
	plot '$2' using 1:2 with linespoints lc rgb '#000000FF' title 'Avec Appli Qt'" | gnuplot

if [ $? != 0 ]  
then
	echo "Echec de la création de $NAME"
else
	echo "Création de $NAME réussie"
fi







