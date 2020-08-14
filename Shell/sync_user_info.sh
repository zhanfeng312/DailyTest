#!/bin/sh

PASSWD_FILE_NAME="passwd"

function sync_passwd_info()
{
    while read line || [[ -n $line ]]
    do
        echo "The line is $line"
    done < ${PASSWD_FILE_NAME}
}

sync_passwd_info