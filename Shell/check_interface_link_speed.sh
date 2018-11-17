#!/bin/sh

ETHTOOL="/root/bin/ethtool"
INTERFACE_NAME="eth0"
MATCH_PATTERN="Speed: 10Mb/s"
IFCONFIG="/sbin/ifconfig"
DOWN_UP_INTERVAL_TIME=1
SLEEP_TIME=2

while true
do	
	${ETHTOOL} ${INTERFACE_NAME} | grep "${MATCH_PATTERN}" &>/dev/null
	
	if [ $? -eq 0 ]; then
	
		${IFCONFIG} ${INTERFACE_NAME} down
		sleep ${DOWN_UP_INTERVAL_TIME}
		${IFCONFIG} ${INTERFACE_NAME} up
		${ETHTOOL} -s ${INTERFACE_NAME} autoneg on
	fi
	sleep ${SLEEP_TIME}
done
