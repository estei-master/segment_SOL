#! /bin/bash

i=0
j=0
k=0
latitude=44.86
longitude=-0.5
heures=11h35m28

while [[ $k -ne 10 ]]
do
	longitude=-0.50$i
	latitude=44.86$j
	heures=11h35m$k
	let i++
	let j++
	let k++
	trame=$latitude,$longitude,$heures,
	echo $trame
	echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt				
	sleep 1
done
