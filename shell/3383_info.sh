#!/bin/sh

if [ $# -ne 1 ];then
	IMAGEINDEX="2"
else
	IMAGEINDEX="$1"
fi

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/system/lib

SNMPBINDIR=/system/bin
SNMPGET=${SNMPBINDIR}/snmpget
SNMPSET=${SNMPBINDIR}/snmpset
SED="busybox sed"
IFCONFIG="busybox ifconfig"
PINGTIMEOUT=10
CM_FACTORY_IP_ADDR=192.168.100.1

if [ ! -x ${SNMPGET} ] || [ ! -x ${SNMPSET} ];then
	echo "snmp app not avalible"
	exit 1
fi

i=0
PING_SUCCESS=
while [ $i -lt ${PINGTIMEOUT} ];do
	busybox ping -w 1 -c 1 ${CM_FACTORY_IP_ADDR} &>/dev/null
	if [ $? -eq 0 ];then
		PING_SUCCESS=1
		break;
	fi
	let i++
done
if [ -z "${PING_SUCCESS}" ];then
	echo "ping host failed"
	exit 1
fi

${SNMPSET} -v 2c -c private ${CM_FACTORY_IP_ADDR} .1.3.6.1.4.1.4413.2.99.1.1.1.2.1.2.1 s password &>/dev/null

if [ $? -ne 0 ];then
	echo "can not set password"
	exit 1
fi

SW_VERSION=`${SNMPGET} -v 2c -c public ${CM_FACTORY_IP_ADDR} .1.3.6.1.2.1.1.1.0 2>/dev/null | ${SED} 's/^.*W_REV: //g' | ${SED} 's/; MODEL.*$//g'`

CRC=`${SNMPGET} -C h -v 2c -c public ${CM_FACTORY_IP_ADDR} .1.3.6.1.4.1.4413.2.99.1.1.2.4.2.2.1.1.10.${IMAGEINDEX} 2>/dev/null | grep "SNMP_HEX:" | ${SED} 's/^.*://g'`

MAC_HFC=`${SNMPGET} -O x -v 2c -c public ${CM_FACTORY_IP_ADDR} .1.3.6.1.4.1.4413.2.99.1.1.2.1.4.1.2.1 2>/dev/null | grep "= Hex-STRING:" | ${SED} 's/^.*: //g'`

MAC_ROUTER=`${SNMPGET} -O x -v 2c -c public ${CM_FACTORY_IP_ADDR} .1.3.6.1.4.1.4413.2.99.1.1.2.1.4.1.2.3 2>/dev/null | grep "= Hex-STRING:" | ${SED} 's/^.*: //g'`

MAC_WLAN=`${SNMPGET} -O x -v 2c -c public ${CM_FACTORY_IP_ADDR} .1.3.6.1.4.1.4413.2.99.1.1.2.1.4.1.2.12 2>/dev/null | grep "= Hex-STRING:" | ${SED} 's/^.*: //g'`

echo "********************************************"
echo "IMAGE:      ${IMAGEINDEX}"
echo "SW_VER:     ${SW_VERSION}"
echo "CRC:        ${CRC}"
echo "MAC_HFC:    ${MAC_HFC}"
echo "MAC_ROUTER: ${MAC_ROUTER}"
echo "MAC_WLAN:   ${MAC_WLAN}"
echo "********************************************"
