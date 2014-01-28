#! /bin/bash

i=0
k=100
niveauBatterie=$k

while [[ $i -ne 205 ]]
do
	if [[ $k -ne -1 ]]
	then
		niveauBatterie=$k
		let k--
		echo $niveauBatterie > /home/pierre/Documents/batterie/niveauBatterie.txt
		sleep 1
	else
		k=100
	fi
	let i++
done

kill testNiveauBatterie.sh
