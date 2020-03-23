#!/bin/bash

export ROS_IP=$(hostname -I)
export ROS_MASTER_URI=http://$(echo $SSH_CLIENT | awk '{ print $1}' | grep -v -e '^$'):11311 # get the ip of the person initing the ssh connection (presumably roscore)

touch frank_was_here;
source ~/ghettoBot/devel/setup.sh

exec "$@"