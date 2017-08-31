#!/bin/sh

# change mode of stb for gehua_9842cm3
ISTC_CLI=/root/bin/istc_cli

if [ -x ${ISTC_CLI} ]; then
    echo -e "ip\nsetmode eth1 static\nsetmode vth1 static\nsetmode eth0 dhcp" >/tmp/change_mode
    ${ISTC_CLI} -S /tmp/change_mode
else
	echo "istc_cli is not exists or not be executable!"
    exit 1
fi
