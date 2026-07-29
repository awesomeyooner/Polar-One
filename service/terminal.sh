#!/bin/bash

NAME=ros2
TAG=jazzy

CONTAINER_NAME="polarone-terminal"

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

docker run \
    -it \
    --init \
    --rm \
    --hostname container \
    --name ${CONTAINER_NAME} \
    --user $(id -u):$(id -g) \
    --volume "$(dirname "$(realpath "$0")")/../ros2_ws":/home/ubuntu/ros2_ws \
    --net=host \
    -e TERM=xterm-256color \
    --group-add $(getent group dialout | cut -d: -f3) \
    --group-add $(getent group tty | cut -d: -f3) \
    --group-add $(getent group video | cut -d: -f3) \
    --device-cgroup-rule='c 13:* rmw' \
    --device-cgroup-rule='c 166:* rmw' \
    --device-cgroup-rule='c 188:* rmw' \
    --device-cgroup-rule='c 81:* rmw' \
    --device-cgroup-rule='c 189:* rmw' \
    -v /dev:/dev \
    ${NAME}:${TAG} \
    $*