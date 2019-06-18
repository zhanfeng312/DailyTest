#!/bin/sh

IMAGE_NAME=ubuntu:1404_V0200
#IMAGE_NAME=ubuntu:1404_test

### yanghuang@ubuntu:~$ id
### uid=1000(yanghuang) gid=1000(yanghuang) groups=1000(yanghuang),999(docker)
USER_ID=1000
GROUP_ID=1000

OPT_DIR="/opt"
ISDK_DIR="/iSDK"
OTHER_SYMBOLIC_DIR_SRC="/mnt/sdb/iSDK"
OTHER_SYMBOLIC_DIR1_SRC="/mnt/sdb/opt"

BUILD_DIR="/mnt/sdb/build_env"


docker run -it --rm \
    --mount type=bind,source=$HOME/.gitconfig,target=/home/yang/.gitconfig \
    --mount type=bind,source=$HOME/.ssh,target=/home/yang/.ssh \
    --mount type=bind,source=$HOME/.subversion,target=/home/yang/.subversion \
    --mount type=bind,source=/etc/hosts,target=/etc/hosts \
    --mount type=bind,source=$OPT_DIR,target=/opt \
    --mount type=bind,source=$ISDK_DIR,target=/iSDK \
    --mount type=bind,source=$OTHER_SYMBOLIC_DIR_SRC,target=$OTHER_SYMBOLIC_DIR_SRC \
    --mount type=bind,source=$OTHER_SYMBOLIC_DIR1_SRC,target=$OTHER_SYMBOLIC_DIR1_SRC \
    --mount type=bind,source=$BUILD_DIR,target=/mnt/build_env \
    $IMAGE_NAME $USER_ID $GROUP_ID
