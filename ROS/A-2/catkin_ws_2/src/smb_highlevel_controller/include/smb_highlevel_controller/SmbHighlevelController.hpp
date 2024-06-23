#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>


namespace smb_highlevel_controller {

/*!
 * Class containing the Husky Highlevel Controller
 */
class SmbHighlevelController {
public:
	/*!
	 * Constructor.
	 */
	SmbHighlevelController(ros::NodeHandle& nodeHandle);

	/*!
	 * Destructor.
	 */
	virtual ~SmbHighlevelController();

private:
	void call(const sensor_msgs::LaserScan &msg);
	ros::NodeHandle nodeHandle;
	ros::Subscriber subscriber;
};

} /* namespace */
