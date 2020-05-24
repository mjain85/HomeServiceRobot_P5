#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

bool atPickup = false;
bool atDropoff = false;
bool pickedUp = false;
bool dropped = false;
bool atStart = false;
double pickup[3] = {-4,1,1.0};
double dropoff[3] = {-1,2,-0.5};

void checkRobotState(const nav_msgs::Odometry::ConstPtr& msg)
{
  //dist with pickup
  //ROS_INFO("Inside Check Func");
  float th = 0.75;
  ROS_INFO_STREAM("Robot Location :" << msg->pose.pose.position.x << ", " << msg->pose.pose.position.y <<"," << msg->pose.pose.orientation.w);
  if(std::abs(msg->pose.pose.position.x - pickup[0]) < th && std::abs(msg->pose.pose.position.y - pickup[1]) < th)
    atPickup = true;
  if(std::abs(msg->pose.pose.position.x - dropoff[0]) < th && std::abs(msg->pose.pose.position.y - dropoff[1]) < th)
    atDropoff = true;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber sub = n.subscribe("odom", 1000, checkRobotState);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickup[0];
    marker.pose.position.y = pickup[1];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = pickup[2];

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0/4;
    marker.scale.y = 1.0/4;
    marker.scale.z = 1.0/4;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    if(pickedUp==false && !atPickup && !atStart)
    {
    	marker_pub.publish(marker);
    	ROS_INFO("publish makers at pickup zone");
	atStart = true;
    	ros::Duration(1.0).sleep();
     }
     else if(pickedUp == false && atPickup)
     {
	//ros::Duration(1.0).sleep();
	marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        pickedUp = true;
	ROS_INFO("Remove makers from pickup zone");
     }
     if(atDropoff && dropped==false)
     {
    	// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
	  marker.action = visualization_msgs::Marker::ADD;
	  marker.pose.position.x = dropoff[0];
	  marker.pose.position.y = dropoff[1];
	  marker.pose.position.z = 0;
	  marker.pose.orientation.x = 0.0;
	  marker.pose.orientation.y = 0.0;
	  marker.pose.orientation.z = 0.0;
	  marker.pose.orientation.w = dropoff[2];
	  marker_pub.publish(marker);
	  dropped = true;
          ros::Duration(1.0).sleep();
	  ROS_INFO("Added makers at Dropoff zone");
     }
    ros::spinOnce();
    r.sleep();
  }
}
