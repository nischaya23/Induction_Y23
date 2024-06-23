#include <ros/ros.h>
#include "smb_highlevel_controller/SmbHighlevelController.hpp"


void call(){
  ROS_INFO_STREAM("Read topic");
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "smb_highlevel_controller");
  ros::NodeHandle nodeHandle("~");


  smb_highlevel_controller::SmbHighlevelController smbHighlevelController(nodeHandle);

  ros::spin();
  return 0;
}
