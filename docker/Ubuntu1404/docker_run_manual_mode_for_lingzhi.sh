#!/bin/sh

#this is for compile istb3 in local

IMAGE_NAME=ubuntu:1404_V0300_lingzhi
#IMAGE_NAME=ubuntu:1404_V0100
#IMAGE_NAME=ubuntu:1404_V0200
#IMAGE_NAME=ubuntu:1404_test

### yanghuang@ubuntu:~$ id
### uid=1000(yanghuang) gid=1000(yanghuang) groups=1000(yanghuang),999(docker)
USER_ID=1000
GROUP_ID=1000

OPT_DIR="/opt"
BUILD_DIR="/home/inspur/build_env"

docker run -it --rm \
    --mount type=bind,source=$HOME/.gitconfig,target=/home/yang/.gitconfig \
    --mount type=bind,source=$HOME/.ssh,target=/home/yang/.ssh \
    --mount type=bind,source=$HOME/.subversion,target=/home/yang/.subversion \
    --mount type=bind,source=/etc/hosts,target=/etc/hosts \
    --mount type=bind,source=$OPT_DIR,target=/opt \
    --mount type=bind,source=$BUILD_DIR,target=/mnt/build_env \
    $IMAGE_NAME $USER_ID $GROUP_ID "local_compile"
