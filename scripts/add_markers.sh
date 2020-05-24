#!/bin/sh

export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/catkin_ws/src/map/map.yaml

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch"  &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch"  &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 10
xterm  -e  " rosrun pick_objects pick_objects" &
sleep 10
xterm  -e  " rosrun add_markers add_markers"
