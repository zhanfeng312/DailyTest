#!/bin/sh

groupadd -g $2 yang
useradd -u $1 -g $2 yang

chown $1:$2 /home/yang -R

su - yang -c "chmod 700 /home/yang/.ssh"

exec bash -c "su yang"