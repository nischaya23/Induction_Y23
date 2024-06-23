#include <smb_highlevel_controller/SmbHighlevelController.hpp>



namespace smb_highlevel_controller {

SmbHighlevelController::SmbHighlevelController (ros::NodeHandle& n) :
  nodeHandle(n)
{
  std::string topic;
  int queue_size;
  if ( !n.getParam("scan_topic", topic) 
        || !n.getParam("queue_size", queue_size) ) 
    {
        ROS_ERROR("PARAMS NOT FOUND!"); 
    }
    subscriber=n.subscribe(topic,queue_size,&SmbHighlevelController::call,this);
    ROS_INFO("Node Started");
}
void SmbHighlevelController::call(const sensor_msgs::LaserScan &msg){
  //ROS_INFO_STREAM("Connected to scan");
  auto min_elem = std::min_element(msg.ranges.cbegin(), msg.ranges.cend());
  ROS_INFO_STREAM("Closest distance is " << *min_elem);
}


SmbHighlevelController::~SmbHighlevelController()
{
}

} /* namespace */
