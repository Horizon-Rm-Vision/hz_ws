
// #ifndef STANDARD_ROBOT_PP_ROS2__STANDARD_ROBOT_PP_ROS2_HPP_
// #define STANDARD_ROBOT_PP_ROS2__STANDARD_ROBOT_PP_ROS2_HPP_

// #include <memory>
// #include <string>
// #include <unordered_map>
// #include <vector>
// #include <Eigen/Geometry>
// #include "example_interfaces/msg/float64.hpp"
// #include "example_interfaces/msg/u_int8.hpp"
// #include "geometry_msgs/msg/twist.hpp"
// #include "pb_rm_interfaces/msg/judge_data.hpp"
// #include "pb_rm_interfaces/msg/gimbal_cmd.hpp"
// #include "rm_interfaces/msg/gimbal_cmd.hpp"
// #include "rclcpp/rclcpp.hpp"
// #include "sensor_msgs/msg/imu.hpp"
// #include "sensor_msgs/msg/joint_state.hpp"
// #include "serial_driver/serial_driver.hpp"
// #include "standard_robot_pp_ros2/packet_typedef.hpp"
// #include "standard_robot_pp_ros2/robot_info.hpp"
// #include "std_msgs/msg/int8.hpp"
// #include <tf2_ros/transform_broadcaster.h>
// #include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
// namespace standard_robot_pp_ros2
// {
// class StandardRobotPpRos2Node : public rclcpp::Node
// {
// public:
//   explicit StandardRobotPpRos2Node(const rclcpp::NodeOptions & options);

//   ~StandardRobotPpRos2Node() override;

// private:
//   bool is_usb_ok_;
//   bool debug_;
//   std::unique_ptr<IoContext> owned_ctx_;
//   std::string device_name_;
//   std::unique_ptr<drivers::serial_driver::SerialPortConfig> device_config_;
//   std::unique_ptr<drivers::serial_driver::SerialDriver> serial_driver_;
//   bool record_rosbag_;
//   bool set_detector_color_;

//   std::thread receive_thread_;
//   std::thread send_thread_;
//   std::thread serial_port_protect_thread_;

//   // Publish
//   // rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
//   rclcpp::Publisher<pb_rm_interfaces::msg::JudgeData>::SharedPtr judge_data_pub_;
//   rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
//   // rclcpp::Publisher<pb_rm_interfaces::msg::JudgeData::mode>::SharedPtr mode_pub;
//   // Subscribe
//   rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
//   rclcpp::Subscription<pb_rm_interfaces::msg::JudgeData>::SharedPtr cmd_model_sub_;
//   rclcpp::Subscription<pb_rm_interfaces::msg::JudgeData>::SharedPtr cmd_mode_sub_;
//   rclcpp::Subscription<rm_interfaces::msg::GimbalCmd>::SharedPtr shijue_sub_1;
//   rclcpp::Subscription<rm_interfaces::msg::GimbalCmd>::SharedPtr shijue_sub_2;

//   RobotModels robot_models_;
//   std::unordered_map<std::string, rclcpp::Publisher<example_interfaces::msg::Float64>::SharedPtr>
//     debug_pub_map_;

//   SendRobotCmdData send_robot_cmd_data_;

//   void getParams();
//   void createPublisher();
//   void createSubscription();
//   void createNewDebugPublisher(const std::string & name);
//   void receiveData();
//   void sendData();
//   void serialPortProtect();
//   void publishJudgeData(JudgeData & data);
//   void publishMode(int &mode);
//   void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);
//   void modleCallback(const pb_rm_interfaces::msg::JudgeData::SharedPtr msg);
//   void aimCallback(const rm_interfaces::msg::GimbalCmd::SharedPtr msg);
//   void setParam(const rclcpp::Parameter & param);
//   bool getDetectColor(uint8_t robot_id, uint8_t & color);
//   bool callTriggerService(const std::string & service_name);
//   Eigen::Vector3d getRPY(const Eigen::Matrix3d &R);
//   // Param client to set detect_color
//   using ResultFuturePtr = std::shared_future<std::vector<rcl_interfaces::msg::SetParametersResult>>;
//   bool initial_set_param_ = false;
//   uint8_t previous_receive_color_ = 0;
//   rclcpp::AsyncParametersClient::SharedPtr detector_param_client_;
//   ResultFuturePtr set_param_future_;
//   std::string detector_node_name_;
//   uint8_t previous_game_progress_ = 0;
//   float last_hp_;
//   float last_gimbal_pitch_odom_joint_, last_gimbal_yaw_odom_joint_;
//   double timestamp_offset_ = 0;
//   std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
//   std::string target_frame_;
// };
// }  // namespace standard_robot_pp_ros2

// #endif  // STANDARD_ROBOT_PP_ROS2__STANDARD_ROBOT_PP_ROS2_HPP_