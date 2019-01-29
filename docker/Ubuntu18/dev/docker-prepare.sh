#!/bin/sh

#uid=1001 gid=1001

USER_ID=`id | sed -e 's/^uid=//g;s/ .*$//g'`
GROUP_ID=`id | sed -e 's/^uid=//g;s/ .*$//g'`

isudo "groupadd -g ${GROUP_ID} yang" &> /dev/null
isudo "useradd -u ${USER_ID} -g ${GROUP_ID} yang" &> /dev/null
isudo "chown ${USER_ID}:${GROUP_ID} /home/yang -R" &> /dev/null

isudo "exec bash -c 'su - yang'" 
