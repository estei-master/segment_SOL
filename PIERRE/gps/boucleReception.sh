#! /bin/bash

i=0
j=0
k=100
latitude=12.$i
longitude=56.$j
heures=11h35m28s
niveauBatterie=$k
nbSatellites=5
trame=0

while [ 1 ]
do
	let i++
	let j++
	let k--
	latitude=12.$i
	longitude=56.$j
	niveauBatterie=$k%
	trame=$latitude,$longitude,$heures,$nbSatellites,
	echo $trame
	echo $niveauBatterie
	echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt
	echo $niveauBatterie > /home/pierre/Documents/GPS/niveauBatterie.txt
	sleep 3
done
