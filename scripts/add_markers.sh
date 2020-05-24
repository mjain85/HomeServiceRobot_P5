#!/bin/sh

export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/catkin_ws/src/map/map.yaml

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch"  &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch"  &
sleep 5
xterm  -e  " rosrun rviz rviz -d /home/workspace/catkin_ws/src/rvizConfig/viewNavigation.rviz" &
sleep 5
#xterm  -e  " rosrun pick_objects pick_objects" &
#sleep 1
xterm  -e  " rosrun add_markers_old add_markers_old"
