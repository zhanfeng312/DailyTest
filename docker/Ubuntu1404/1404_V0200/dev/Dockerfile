FROM ubuntu:1404_V0100

RUN buildDeps='dpkg-dev gnupg flex bison gperf lib32stdc++6 libsdl1.2-dev libesd0-dev libncurses5-dev zlib1g-dev uuid-runtime build-essential libc6-dev-i386 python-m2crypto liblzo2-dev:i386 uuid-dev:i386 libswitch-perl libxml2-utils lib32z1 zlibc zlib1g-dbg default-jre default-jdk libglib2.0-0:i386 scons xz-utils'\
    && dpkg --add-architecture i386 \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && wget http://ftp.gnu.org/gnu/make/make-3.82.tar.bz2 \
    && tar -jxf make-3.82.tar.bz2  \
    && cd make-3.82 \
    && ./configure \
    && make \
    && make install \
    && cd - \
    && rm -rf make-3.82* \
    && apt-get purge -y --auto-remove make
