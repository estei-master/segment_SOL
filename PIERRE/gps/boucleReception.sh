#! /bin/bash

i=0
j=0
latitude=12.$i
longitude=56.$j
heures=11h35m28s
niveauBatterie=35
nbSatellites=5
trame=0

while [ 1 ]
do
	let i++
	let j++
	latitude=12.$i
	longitude=56.$j
	trame=$latitude,$longitude,$heures,$niveauBatterie,$nbSatellites
	echo $trame
	echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt
	sleep 5
done
