#! /bin/bash

i=1
j=5
l=0
k=0
s=0

latitude=44.86
longitude=-0.5
heures=11h35m28
trame=0

while [[ $k -ne 3 ]]
do

	while [[ $j -ne 8 ]]
	do
		longitude=-0.5$j$l
		latitude=44.86$i
		heures=11h35m$s
		if [[ $l -ne 9 ]]
		then
			let l++
			let s++
			trame=$latitude,$longitude,$heures,
			echo $trame
			echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt		
			sleep 1
		else
			l=0
			let j++
			trame=$latitude,$longitude,$heures,
			echo $trame
 			echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt		
			sleep 1
		fi
	done
	
	while [[ $i -ne 8 ]]
	do
		longitude=-0.5$j$l
		latitude=44.86$i
		heures=11h35m$s
		let i++
		let s++
		trame=$latitude,$longitude,$heures,
		echo $trame
		echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt	
		sleep 1	
	done
	
	while [[ $j -ne 5 || $l -ne 0 ]]
	do
		longitude=-0.5$j$l
		latitude=44.86$i
		heures=11h35m$s
		if [[ $l -ne 0 ]]
		then
			let l--
			let s++
			trame=$latitude,$longitude,$heures,
			echo $trame
			echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt			
			sleep 1
		else
			l=9
			let j--
			trame=$latitude,$longitude,$heures,
			echo $trame
			echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt	
			sleep 1
		fi	
	done
	
	while [[ $i -ne 1 ]]
	do
		longitude=-0.5$j$l
		latitude=44.86$i
		heures=11h35m$s
		j=5
		let i--
		let s++
		trame=$latitude,$longitude,$heures,
		echo $trame
		echo $trame > /home/pierre/Documents/GPS/donneeIHM.txt	
		sleep 1	
	done
	
	let k++
done

killall boucleReception.sh
