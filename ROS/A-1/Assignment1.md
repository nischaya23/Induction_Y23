## DOCKER Ros Start
0. Pulled ros noetic image 
1. Started Docker container 
2. Opened another terminal and connected to same container id
3. moved files to docker container

```bash
docker pull ros:noetic-robot
docker run -it ros:noetic-robot
docker exec -it 9fdf6fabecd6 bash
docker commit a2f3588cbc7f image2:v2 #TO commit previous container to new 
```

## ROS SIDE

cmds-

```bash
mkdir git
mkdir ~/Workspaces
mkdir ./smb_ws
mkdir ./src
```

symlink by
```bash
ln -s /path/to/file /path/to/symlink
```

## CATKIN
```bash
 sudo apt install python3-catkin-tools
 source /opt/ros/noetic/setup.bash
 catkin init  #IN Parent of Src(here smb_ws)
 catkin build #inital build
 source devel/setup.bash
 catkin build #build all files of source
 source devel/setup.bash
 roslaunch smb_gazebo smb_gazebo.launch
```

--For trouble shooting: ***sudo apt install ros-noetic-gazebo-plugins*** and ***rosdep install --from-paths src --ignore-src -r -y*** ,***Sudo apt install ros-noetic-velodyne-description*** and 
***sudo apt install ros-noetic-hector-gazebo-plugins*** when build was not happening properly 


## ROS COMMANDS Output

### rostopic list

/clock <br>
/cmd_vel<br>
/diagnostics<br>
/e_stop<br>
/gazebo/link_states                             <br>
/gazebo/model_states<br>
/gazebo/parameter_descriptions<br>
/gazebo/parameter_updates<br>
/gazebo/performance_metrics<br>
/gazebo/set_link_state<br>
/gazebo/set_model_state<br>
/imu/data<br>
/imu0<br>
/imu0/accel/parameter_descriptions<br>
/imu0/accel/parameter_updates<br>
/imu0/bias<br>
/imu0/rate/parameter_descriptions<br>
/imu0/rate/parameter_updates<br>
/imu0/yaw/parameter_descriptions<br>
/imu0/yaw/parameter_updates<br>
/joint_states<br>
/joy_teleop/cmd_vel<br>
/odometry/filtered<br>
/rosout<br>
/rosout_agg<br>
/rslidar_points<br>
/set_pose<br>
/smb_velocity_controller/cmd_vel<br>
/tf<br>
/tf_static<br>
/twist_marker_server/cmd_vel<br>

### rosnode list

/ekf_localization<br>
/gazebo<br>
/gazebo_gui<br>
/rosout<br>
/smb_robot_state_publisher<br>
/twist_mux<br>


## LAUNCH File

```html

<?xml version="1.0" encoding="utf-8"?>

<launch>

  <!-- GAZEBO ARGUMENTS -->
  <!-- Run Gazebo headless -->
  <arg name="headless"                              default="false"/>
  <!-- Model path -->
  <arg name="model_path"                            default="$(find smb_gazebo)/"/>
  <arg name="robot_namespace"                       default=""/>
  <arg name="robot_model_name"                      default="smb"/>
  <arg name="enable_ekf"                            default="true"/>

  <!-- Name of the world -->
  <arg name="world"                                 default="empty"/>
  <!-- Path to the world file -->
  <arg name="/usr/share/gazebo-11/worlds/robocup14_spl_field.world"                            default="$(find smb_gazebo)/worlds/$(arg world).world"/>
  <arg name="laser_enabled"							            default="true"/>

  <!-- Set the initial pose of the robot's main body -->
  <arg name="x"                                     default="0.0"/>
  <arg name="y"                                     default="0.0"/>
  <arg name="z"                                     default="0.4"/>
  <arg name="roll"                                  default="0.0"/>
  <arg name="pitch"                                 default="0.0"/>
  <arg name="yaw"                                   default="0.0"/>
  <!-- Start paused -->
  <arg name="paused"                                default="false"/>
  <!-- Use simulation clock -->
  <arg name="use_sim_time"                          default="true"/>
  <!-- Debug mode -->
  <arg name="debug"                                 default="false"/>
  <!-- Verbose mode -->
  <arg name="verbose"                               default="true"/>

  <arg name="laser_scan_min_height"                  default="0.0"/>
  <arg name="laser_scan_max_height"                  default="0.1"/>

  <!-- GUI ARGUMENTS -->
  <!-- Enable/disable Gazebo GUI -->
  <arg name="run_gui"                               default="true"/>
  
  <!-- ROBOT ARGUMENTS -->
  <!-- Name of the robot description parameter -->
  <arg name="robot_description" default="robot_description"/>

  <!-- Load Gazebo world -->
  <include file="$(find gazebo_ros)/launch/empty_world.launch">
    <env name="GAZEBO_MODEL_PATH" value="$(arg model_path)"/>
    <arg name="world_name"        value="$(arg world_file)"/>
    <arg name="paused"            value="$(arg paused)"/>
    <arg name="use_sim_time"      value="$(arg use_sim_time)"/>
    <arg name="gui"               value="$(arg run_gui)"/>
    <arg name="headless"          value="$(arg headless)"/>
    <arg name="debug"             value="$(arg debug)"/>
    <arg name="verbose"           value="$(arg verbose)"/>
  </include>

  <!-- Spawn robot in Gazebo -->
  <node name="spawn_urdf" pkg="gazebo_ros" type="spawn_model"
    args="-param $(arg robot_description) -urdf -model $(arg robot_model_name) -x $(arg x)
      -y $(arg y) -z $(arg z) -R $(arg roll) -P $(arg pitch) -Y $(arg yaw)"
    output="screen"/>
    
    
    
  <!-- Convert 3D velodyne scan to laser scan -->
  <node name= "pointcloud_to_laserscan" pkg="pointcloud_to_laserscan" type="pointcloud_to_laserscan_node" if="$(arg laser_enabled)">
        <remap from="cloud_in" to="/rslidar_points"/>
        <remap from="scan" to="/scan"/>
        <rosparam>
            target_frame: rslidar # Leave disabled to output scan in pointcloud frame
            transform_tolerance: 0.01
            min_height: $(arg laser_scan_min_height)
            max_height: $(arg laser_scan_max_height)

            angle_min: -1.5708 # -M_PI/2
            angle_max: 1.5708 # M_PI/2
            angle_increment: 0.0087 # M_PI/360.0
            scan_time: 0.03333
            range_min: 0.45
            range_max: 50.0
            use_inf: true
            inf_epsilon: 1.0

            # Concurrency level, affects number of pointclouds queued for processing and number of threads used
            # 0 : Detect number of cores
            # 1 : Single threaded
            # 2->inf : Parallelism level
            concurrency_level: 1
        </rosparam>
  </node>


  <include file="$(find smb_control)/launch/control.launch">
    <arg name="simulation"      default="true"/>
    <arg name="robot_namespace"     default="$(arg robot_namespace)"/>
    <arg name="robot_description"   default="$(arg robot_description)"/>
    <arg name="enable_ekf"          default="$(arg enable_ekf)" />
  </include>
</launch>
```





TO change **MAP**

```bash
<arg name="world_file" value="/usr/share/gazebo-9/worlds/robocup14_spl_field.world"/>
```

<img src='./img_ros.jpg'>