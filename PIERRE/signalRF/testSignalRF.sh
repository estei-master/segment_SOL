#! /bin/bash

i=0
k=0
signalRF=$k

while [[ $i -ne 40 ]]
do
	if [[ $k -ne 5 ]]
	then
		signalRF=$k
		let k++
		echo $signalRF
		echo $signalRF > /home/pierre/Documents/signalRF/signalRF.txt
		sleep 1
	else
		k=0
	fi
	let i++
done

kill testSignalRF.sh
