/*以下是作出修改的部分
雷达ip末两位为09
建图命令需使用*/
ros2 launch pb2025_nav_bringup rm_navigation_reality_launch.py \
slam:=True \
use_robot_state_pub:=True
/*保存地图的命令*/
ros2 run nav2_map_server map_saver_cli -f <YOUR_MAP_NAME>
/*原名令后加上了车型，但在agx上无法运行遂修改，YOUR_MAP_NAME处修改为scan可以运行其他不可，目前为找到原因*/
/*导航命令运行之前需将自己建好的图和pcd文件移动至相应文件夹内即pb2025_nav_bringup*/
ros2 launch pb2025_nav_bringup rm_navigation_reality_launch.py \
world:=<YOUR_WORLD_NAME> \
slam:=False \
use_robot_state_pub:=True
/*YOUR_WORLD_NAME处应修改为地图名称，建议将地图名称和pcd名称改为相同否则可能会报错;修改完地图名称之后，yaml文件中的名称一并修改否则在rviz中会有显示错误*/
/*进行wp_map_tools插件的融合*//*未实现2025.7.8*/
/*yi shi xian wp_map_tools chajiande ronghe*/
发布消息ros2 topic pub -r 10 /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 1.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"x,y,z速度消息
2025.9.28重定位测试小范围内可用大范围等待登陆实车测验
已作出修改的部分：串口通信，机器人模型测试。
下一步修改方向：重定位small_gicp算法可能有待修改，算法可能不太牛鼻吧
e data in the transform cache'
[component_container_isolated-2] [WARN] [1761660996.866232374] [red_standard_robot1.controller_server]: Control loop missed its desired rate of 20.0000Hz
[component_container_isolated-2] [INFO] [1761660996.947166981] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 28.400 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [INFO] [1761660997.044286875] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 28.450 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [INFO] [1761660997.118030550] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 28.500 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [INFO] [1761660997.120497424] [red_standard_robot1.controller_server]: Passing new path to controller.
[component_container_isolated-2] [INFO] [1761660997.259665626] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 28.550 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [INFO] [1761660997.386132830] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 28.650 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [ERROR] [1761660997.519222813] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 28.950000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660997.519279645] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [WARN] [1761660997.519355909] [red_standard_robot1.controller_server]: Control loop missed its desired rate of 20.0000Hz
[component_container_isolated-2] [INFO] [1761660997.519367045] [red_standard_robot1.controller_server]: Passing new path to controller.
[component_container_isolated-2] [ERROR] [1761660997.662355431] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 29.050000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660997.662424586] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [WARN] [1761660997.662615400] [red_standard_robot1.controller_server]: Control loop missed its desired rate of 20.0000Hz
[component_container_isolated-2] [INFO] [1761660997.806009968] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 28.950 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [ERROR] [1761660997.814869157] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 29.150000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660997.814939941] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [ERROR] [1761660997.814967073] [red_standard_robot1.controller_server]: Controller patience exceeded
[component_container_isolated-2] [WARN] [1761660997.815022032] [red_standard_robot1.controller_server]: [follow_path] [ActionServer] Aborting handle.
[component_container_isolated-2] [INFO] [1761660997.828456251] [red_standard_robot1.local_costmap.local_costmap]: Received request to clear entirely the local_costmap
[component_container_isolated-2] [INFO] [1761660997.828828274] [red_standard_robot1.controller_server]: Received a goal, begin computing control effort.
[component_container_isolated-2] [INFO] [1761660997.868937048] [red_standard_robot1.controller_server]: Passing new path to controller.
[component_container_isolated-2] [INFO] [1761660997.939191021] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.050 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [INFO] [1761660998.017292749] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.100 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [ERROR] [1761660998.020418973] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 29.300000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660998.020497920] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [ERROR] [1761660998.020589518] [tf_help]: Transform data too old when converting from map to odom
[component_container_isolated-2] [ERROR] [1761660998.020595300] [tf_help]: Data time: 29s 304000000ns, Transform time: 28s 850000099ns
[component_container_isolated-2] [WARN] [1761660998.020600986] [red_standard_robot1.controller_server]: Control loop missed its desired rate of 20.0000Hz
[component_container_isolated-2] [INFO] [1761660998.091261620] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.150 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [ERROR] [1761660998.172310726] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 29.400000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660998.172394173] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [ERROR] [1761660998.172694642] [tf_help]: Transform data too old when converting from map to odom
[component_container_isolated-2] [ERROR] [1761660998.172706270] [tf_help]: Data time: 29s 304000000ns, Transform time: 28s 850000099ns
[component_container_isolated-2] [WARN] [1761660998.172713324] [red_standard_robot1.controller_server]: Control loop missed its desired rate of 20.0000Hz
[component_container_isolated-2] [INFO] [1761660998.238559775] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.250 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[rviz2-8] [INFO] [1761660998.310014511] [red_standard_robot1.rviz]: Message Filter dropping message: frame 'odom' at time 28.950 for reason 'discarding message because the queue is full'
[component_container_isolated-2] [INFO] [1761660998.312279826] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.300 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [ERROR] [1761660998.324647200] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 29.450000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660998.324703890] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [ERROR] [1761660998.324721533] [red_standard_robot1.controller_server]: Controller patience exceeded
[component_container_isolated-2] [WARN] [1761660998.324755125] [red_standard_robot1.controller_server]: [follow_path] [ActionServer] Aborting handle.
[component_container_isolated-2] [INFO] [1761660998.324815751] [red_standard_robot1.controller_server]: Received a goal, begin computing control effort.
[component_container_isolated-2] [INFO] [1761660998.379363440] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.350 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[rviz2-8] [INFO] [1761660998.405590017] [red_standard_robot1.rviz]: Message Filter dropping message: frame 'odom' at time 29.050 for reason 'discarding message because the queue is full'
[component_container_isolated-2] [INFO] [1761660998.442166093] [red_standard_robot1.global_costmap.global_costmap]: Message Filter dropping message: frame 'odom' at time 29.400 for reason 'the timestamp on the message is earlier than all the data in the transform cache'
[component_container_isolated-2] [ERROR] [1761660998.456182069] [red_standard_robot1.controller_server]: Exception in transformPose: Lookup would require extrapolation into the future.  Requested time 29.600000 but the latest data is at time 28.850000, when looking up transform from frame [odom] to frame [map]
[component_container_isolated-2] [WARN] [1761660998.456247086] [red_standard_robot1.controller_server]: Unable to transform robot pose into global plan's frame
[component_container_isolated-2] [ERROR] [1761660998.456394927] [tf_help]: Transform data too old when converting from map to odom
[component_container_isolated-2] [ERROR] [1761660998.456405408] [tf_help]: Data time: 29s 549000000ns, Transform time: 28s 850000099ns
解决以上问题的方法为colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release --parallel-workers 1
[component_container_isolated-4] [WARN] [1768575987.309717002] [sensor_scan_generation]: TF lookup failed: Lookup would require extrapolation into the future.  Requested time 1768575986.772427 but the latest data is at time 1768575911.691522, when looking up transform from frame [base_footprint] to frame [front_mid360]. Returning identity.
[component_container_isolated-4] [INFO] [1768575987.544615282] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575977.524165, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [WARN] [1768575987.815980199] [sensor_scan_generation]: TF lookup failed: Lookup would require extrapolation into the future.  Requested time 1768575987.272389 but the latest data is at time 1768575911.691522, when looking up transform from frame [base_footprint] to frame [front_mid360]. Returning identity.
[component_container_isolated-4] [INFO] [1768575988.044663042] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575978.024131, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [WARN] [1768575988.322158596] [sensor_scan_generation]: TF lookup failed: Lookup would require extrapolation into the future.  Requested time 1768575987.772488 but the latest data is at time 1768575911.691522, when looking up transform from frame [base_footprint] to frame [front_mid360]. Returning identity.
[component_container_isolated-4] [INFO] [1768575988.544620595] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575978.524092, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [WARN] [1768575988.828567025] [sensor_scan_generation]: TF lookup failed: Lookup would require extrapolation into the future.  Requested time 1768575988.272278 but the latest data is at time 1768575911.691522, when looking up transform from frame [base_footprint] to frame [front_mid360]. Returning identity.
^C[WARNING] [launch]: user interrupted with ctrl-c (SIGINT)
[joy_node-13] [INFO] [1768575988.976449872] [rclcpp]: signal_handler(signum=2)
[INFO] [sync_slam_toolbox_node-8]: process has finished cleanly [pid 60488]
[INFO] [static_transform_publisher-10]: process has finished cleanly [pid 60492]
[INFO] [robot_state_publisher-3]: process has finished cleanly [pid 60478]
[INFO] [terrainAnalysis-11]: process has finished cleanly [pid 60494]
[INFO] [terrainAnalysisExt-12]: process has finished cleanly [pid 60496]
[INFO] [lifecycle_manager-6]: process has finished cleanly [pid 60484]
[INFO] [pointcloud_to_laserscan_node-7]: process has finished cleanly [pid 60486]
[INFO] [joy_node-13]: process has finished cleanly [pid 60499]
[INFO] [pb_teleop_twist_joy_node-14]: process has finished cleanly [pid 60501]
[INFO] [map_saver_server-5]: process has finished cleanly [pid 60482]
[ERROR] [rviz2-15]: process has died [pid 60503, exit code -11, cmd '/opt/ros/humble/lib/rviz2/rviz2 -d /home/horizon/ros_ws/install/pb2025_nav_bringup/share/pb2025_nav_bringup/rviz/nav2_default_view.rviz --ros-args -r __ns:=/ -r /tf:=tf -r /tf_static:=tf_static'].
[INFO] [joint_state_publisher-2]: process has finished cleanly [pid 60476]
[sync_slam_toolbox_node-8] [INFO] [1768575988.976461930] [rclcpp]: signal_handler(signum=2)
[pointcloud_to_laserscan_node-7] [INFO] [1768575988.976474718] [rclcpp]: signal_handler(signum=2)
[terrainAnalysisExt-12] [INFO] [1768575988.976449648] [rclcpp]: signal_handler(signum=2)
[pointlio_mapping-9] [WARN] [1768575988.976487942] [laserMapping]: catch sig 2
[terrainAnalysis-11] [INFO] [1768575988.976460897] [rclcpp]: signal_handler(signum=2)
[pb_teleop_twist_joy_node-14] [INFO] [1768575988.976483294] [rclcpp]: signal_handler(signum=2)
[component_container_isolated-4] [INFO] [1768575988.976506872] [rclcpp]: signal_handler(signum=2)
[component_container_isolated-4] [INFO] [1768575988.976856779] [waypoint_follower]: Running Nav2 LifecycleNode rcl preshutdown (waypoint_follower)
[component_container_isolated-4] [INFO] [1768575988.977075748] [waypoint_follower]: Cleaning up
[livox_ros_driver2_node-1] [INFO] [1768575988.976528582] [rclcpp]: signal_handler(signum=2)
[lifecycle_manager-6] [INFO] [1768575988.976543122] [rclcpp]: signal_handler(signum=2)
[lifecycle_manager-6] [INFO] [1768575988.976775517] [lifecycle_manager_slam]: Running Nav2 LifecycleManager rcl preshutdown (lifecycle_manager_slam)
[lifecycle_manager-6] [INFO] [1768575988.976915021] [lifecycle_manager_slam]: Terminating bond timer...
[rviz2-15] [INFO] [1768575988.976577310] [rclcpp]: signal_handler(signum=2)
[static_transform_publisher-10] [INFO] [1768575988.976601591] [rclcpp]: signal_handler(signum=2)
[map_saver_server-5] [INFO] [1768575988.976608446] [rclcpp]: signal_handler(signum=2)
[map_saver_server-5] [INFO] [1768575988.976814897] [map_saver]: Running Nav2 LifecycleNode rcl preshutdown (map_saver)
[map_saver_server-5] [INFO] [1768575988.977040687] [map_saver]: Deactivating
[map_saver_server-5] [INFO] [1768575988.977065877] [map_saver]: Destroying bond (map_saver) to lifecycle manager.
[robot_state_publisher-3] [INFO] [1768575988.976617591] [rclcpp]: signal_handler(signum=2)
[map_saver_server-5] [INFO] [1768575988.987549277] [map_saver]: Cleaning up
[map_saver_server-5] [INFO] [1768575988.987644812] [map_saver]: Destroying bond (map_saver) to lifecycle manager.
[map_saver_server-5] [INFO] [1768575989.008767817] [map_saver]: Destroying
[component_container_isolated-4] [INFO] [1768575988.993561229] [waypoint_follower]: Destroying bond (waypoint_follower) to lifecycle manager.
[component_container_isolated-4] [INFO] [1768575988.993626931] [bt_navigator]: Running Nav2 LifecycleNode rcl preshutdown (bt_navigator)
[component_container_isolated-4] [INFO] [1768575988.993664297] [bt_navigator]: Cleaning up
[component_container_isolated-4] [INFO] [1768575989.044675348] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575979.024101, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[lifecycle_manager-6] [INFO] [1768575989.002637697] [lifecycle_manager_slam]: Destroying lifecycle_manager_slam
[pointlio_mapping-9] lidar_type: 1
[pointlio_mapping-9] ~~~~/home/horizon/ros_ws/src/pb2025_sentry_nav/point_lio/ file opened
[pointlio_mapping-9] first imu time: 1768575839.725456
[INFO] [pointlio_mapping-9]: process has finished cleanly [pid 60490]
[ERROR] [launch]: Caught exception in launch (see debug for traceback): Cannot shutdown a ROS adapter that is not running
[livox_ros_driver2_node-1] Livox Lidar SDK Deinit completely!
[livox_ros_driver2_node-1] lddc destory!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
[component_container_isolated-4] [WARN] [1768575989.385036824] [sensor_scan_generation]: TF lookup failed: Lookup would require extrapolation into the future.  Requested time 1768575988.822487 but the latest data is at time 1768575911.691522, when looking up transform from frame [base_footprint] to frame [front_mid360]. Returning identity.
[component_container_isolated-4] [INFO] [1768575989.544784790] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575979.224223, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[ERROR] [livox_ros_driver2_node-1]: process has died [pid 60474, exit code -11, cmd '/home/horizon/ros_ws/install/livox_ros_driver2/lib/livox_ros_driver2/livox_ros_driver2_node --ros-args -r __node:=livox_ros_driver2 -r __ns:=/ --params-file /tmp/launch_params_e0o254q8'].
[component_container_isolated-4] [INFO] [1768575990.044746894] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575979.224223, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575990.544783712] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575979.224223, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575991.044674654] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575979.224223, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575991.544622122] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575981.163967, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575992.044689997] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575981.163967, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575992.544749998] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575981.163967, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575993.044761393] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575981.163967, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575993.544753225] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the ea[rviz2-15] [ERROR] [1768616739.076977911] [rviz2]: Vertex Program:rviz/glsl120/indexed_8bit_image.vert Fragment Program:rviz/glsl120/indexed_8bit_image.frag GLSL link result : 
[rviz2-15] active samplers with a different type refer to the same texture image unit
rliest data is at time 1768575981.163967, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575994.044771440] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575981.163967, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[ERROR] [component_container_isolated-4]: process[component_container_isolated-4] failed to terminate '5' seconds after receiving 'SIGINT', escalating to 'SIGTERM'
[INFO] [component_container_isolated-4]: sending signal 'SIGTERM' to process[component_container_isolated-4]
[component_container_isolated-4] [INFO] [1768575994.226847791] [rclcpp]: signal_handler(signum=15)
[component_container_isolated-4] [INFO] [1768575994.228574830] [bt_navigator]: Completed Cleaning up
[component_container_isolated-4] [INFO] [1768575994.228617039] [bt_navigator]: Destroying bond (bt_navigator) to lifecycle manager.
[component_container_isolated-4] [INFO] [1768575994.228623284] [lifecycle_manager_navigation]: Running Nav2 LifecycleManager rcl preshutdown (lifecycle_manager_navigation)
[component_container_isolated-4] [INFO] [1768575994.544605558] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575984.523869, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575995.044601675] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575985.023851, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575995.544605457] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575985.523856, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575996.044643610] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575986.023830, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575996.544745375] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575986.523789, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575997.044641423] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575987.023842, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575997.544594412] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575987.523749, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[component_container_isolated-4] [INFO] [1768575998.044605871] [local_costmap.local_costmap]: Timed out waiting for transform from gimbal_yaw_fake to odom to become available, tf error: Lookup would require extrapolation into the past.  Requested time 1768575911.691522 but the earliest data is at time 1768575988.023689, when looking up transform from frame [gimbal_yaw_fake] to frame [odom]
[rviz2-15] [ERROR] [1768616739.076977911] [rviz2]: Vertex Program:rviz/glsl120/indexed_8bit_image.vert Fragment Program:rviz/glsl120/indexed_8bit_image.frag GLSL link result : 
[rviz2-15] active samplers with a different type refer to the same texture image unit
ros2 launch pb2025_nav_bringup rm_navigation_simulation_launch.py \
slam:=True

