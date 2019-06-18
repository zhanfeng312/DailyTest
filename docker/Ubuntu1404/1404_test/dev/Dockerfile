FROM ubuntu:1404_V0200


RUN buildDeps='bc libglib2.0-0:i386' \
    && dpkg --add-architecture i386 \
    && apt-get update \
    && apt-get install -y $buildDeps