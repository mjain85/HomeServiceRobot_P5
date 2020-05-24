#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  double pickup[3] = {-4,2,1.0};
  double dropoff[3] = {-1,2.5,-0.5};
  // Initialize the simple_navigation_goals node
  
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  ros::Publisher robState_pub = n.advertise<std_msgs::UInt8>("/robot_state", 1);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = pickup[0];
  goal.target_pose.pose.position.y = pickup[1];
  goal.target_pose.pose.orientation.w = pickup[2];

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("The Robot Reached pickup zone");
    std_msgs::UInt8 msgState;
    msgState.data = 1;
    robState_pub.publish(msgState);
    //wait for 5 seconds before move to dropoff zone
    ros::Duration(5.0).sleep();
    
    goal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = dropoff[0];
    goal.target_pose.pose.position.y = dropoff[1];
    goal.target_pose.pose.orientation.w = dropoff[2];

     // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending to dropzone goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult(ros::Duration(50.0));
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        std_msgs::UInt8 msgState;
        msgState.data = 2;
        robState_pub.publish(msgState);
    	ROS_INFO("The Robot Reached drop off zone");
    }
    else
    {
    	ROS_INFO("The base failed to move to drooff zone for some reason");  
    }
  } 
  else
    ROS_INFO("The base failed to move to pickup zone for some reason");

  return 0;
}
