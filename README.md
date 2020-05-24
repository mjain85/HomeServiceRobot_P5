# HomeServiceRobot_P5

The goal of this project is to perform slam using GMapping, navigate thouugh environment and perform path planning and perform task such as pick up and drop off. 
The following steps were taken:

## a. Added official ROS package: 
 - gmapping: To perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.
 - turtlebot_teleop: To control a robot using keyboard commands.
 - turtlebot_rviz_launchers: To load a preconfigured rviz workspace. You’ll save a lot of time by launching this file, because it will automatically load the robot model, trajectories, and map for you.
 - turtlebot_gazebo: To deploy a turtlebot in a gazebo environment by linking the world file to it.

## b. Created following packages:
- map : to hold the map file for navigation. The file was created using test_slam.sh && rosrun map_server map_saver to create the yaml and pgm file
- script : hold all the scripts
- add_markers : The package is created for showing the visual marker for pickup and dropoff once robot reach to corresponding location.
- add_markers_old : to show the visual marker for 5 seconds at pickup location and drop zone after 5 seconds
- pick_objects : The package is responsible to move the robot at 2 different location.
add_marker and pick_object communicate using advertise (/robot_state). Odomotry message was also added but some uncertinity in location cause some confusion.

## c. RViz :
  We also created another rviz file to have marker subsribe. The location of modified file is at 
  "src>turtlebot_interactions>turtlebot_rviz_launchers>rviz/viewNavigation.rviz" and corresponding launch file is at
   "src>turtlebot_interactions>turtlebot_rviz_launchers>launch/view_Navigation_HSR.launch
   
 
## d. Script:
- test_slam.sh : To produce the map using gmapping slam
- test_navigation.sh : to test navigation to validate the map create using slam in previous step
- add_marker.sh : to isualize the marker without navigation
- home_service.sh : Full navigation with path planning
