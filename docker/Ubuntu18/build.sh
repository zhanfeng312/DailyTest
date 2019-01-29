#!/bin/sh

IMAGE_NAME=ubuntu:1804_V0100

docker image rm $IMAGE_NAME
docker build -t $IMAGE_NAME ./dev
