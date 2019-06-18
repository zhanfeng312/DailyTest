#!/bin/sh

IMAGE_NAME=ubuntu:1404_V0300_lingzhi

docker image rm $IMAGE_NAME
docker build -t $IMAGE_NAME ./dev
