#!/bin/bash                                          
### BEGIN INIT INFO
# Provides:          pbit
# Required-Start:   
# Required-Stop:   
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start daemon at boot time
# Description:       Enable service provided by daemon.
### END INIT INFO


LIMIT=50

usage()
{
        echo "-----------------------"
        echo "Usage: $0 (stop|start|restart)"
        echo "-----------------------"
}
 
if [ -z $1 ]; then
        usage
fi
 
service_start()
{
        echo q | /usr/local/bin/fbvis /home/PJ/PBIT.png
	sleep 5
	if [ $(cat /sys/class/power_supply/battery/capacity) -ge $LIMIT ]  
	then
		echo q | /usr/local/bin/fbvis /home/PJ/PBIT_OK.png
		cd /home
		sleep 2
		./horizon.sh
	else
		echo q | fbvis /home/PJ/PBIT_Failed.png
	fi
}
 
service_stop()
{
	echo q | /usr/local/bin/fbvis /home/PJ/Goodbye.png
}
 
case $1 in
        stop)
                service_stop
        ;;
        start)
                service_start
        ;;
        restart)
                service_stop
                service_start
        ;;
        *)
                usage
esac
exit 0

