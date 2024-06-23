## ASSIGNMENT2

1. Downloaded the zip file and added to the catkin_ws_2

2. I have uploaded my catkin_ws_2 with all files that I changed.

3. To create a subscriber of scan topic 

```c++
 std::string topic;
  int queue_size;
  if ( !n.getParam("scan_topic", topic) 
        || !n.getParam("queue_size", queue_size) ) 
    {
        ROS_ERROR("PARAMS NOT FOUND!"); 
    }
    subscriber=n.subscribe(topic,queue_size,&SmbHighlevelController::call,this);
    ROS_INFO("Node Started");
```

4. I also changed the included hpp file to add type of call function that will called everytime a publisher publishes something.
```c++
	void call(const sensor_msgs::LaserScan &msg);
```

5. Created parameter file in cofig folder with parameter topic name and queue size.

6. CallBack Method:
```c++
void SmbHighlevelController::call(const sensor_msgs::LaserScan &msg){
  //ROS_INFO_STREAM("Connected to scan");
  auto min_elem = std::min_element(msg.ranges.cbegin(), msg.ranges.cend());
  ROS_INFO_STREAM("Closest distance is " << *min_elem);
}
```

7. Launch File: 
I used Single Pillar World Here 

```html
<?xml version="1.0"?>
<launch>

  <include file="$(find smb_gazebo)/launch/smb_gazebo.launch">
  <arg name="world_file" value="$(find smb_highlevel_controller)/world/singlePillar.world"/>
  </include>
  <node name="smb_highlevel_controller" pkg="smb_highlevel_controller" type="smb_highlevel_controller" output="screen">
  <rosparam command="load"
  file="$(find smb_highlevel_controller)/config/params.yaml" />
  </node>
    <node name="rviz" pkg="rviz" type="rviz" output="screen" />
</launch>
```



### IMAGES
<img src='./image1.jpeg'>
<img src='./Image2.jpeg'>

### TERMINAL

1. TELEOP KEYBOARD 
 ```bash
sudo apt-get install ros-noetic-teleop-twist-keyboard
rosrun teleop_twist_keyboard teleop_twist
  ```

2. RVIZ
```bash
sudo apt-get install ros-noetic-rviz
```

3.POINT TO LASER NODE
```bash
sudo apt install ros-kinetic-pointcloud-to-laserscan
```
