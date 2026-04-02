// #include "standard_robot_pp_ros2/standard_robot_pp_ros2.hpp"
// #include <memory>
// #include "standard_robot_pp_ros2/crc8_crc16.hpp"
// #include "standard_robot_pp_ros2/packet_typedef.hpp"
// #include "std_srvs/srv/trigger.hpp"
// #include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
// #include <tf2/LinearMath/Matrix3x3.h>
// #include <Eigen/Geometry>
// #define USB_NOT_OK_SLEEP_TIME 1000   // (ms)
// #define USB_PROTECT_SLEEP_TIME 1000  // (ms)
// using namespace std::chrono_literals;
// namespace standard_robot_pp_ros2
// {

// StandardRobotPpRos2Node::StandardRobotPpRos2Node(const rclcpp::NodeOptions & options)
// : Node("StandardRobotPpRos2Node", options),
//   owned_ctx_{new IoContext(2)},
//   serial_driver_{new drivers::serial_driver::SerialDriver(*owned_ctx_)}
// {
//   RCLCPP_INFO(get_logger(), "Start StandardRobotPpRos2Node!");
//   getParams();
//   createPublisher();
//   createSubscription();
//   serial_port_protect_thread_ = std::thread(&StandardRobotPpRos2Node::serialPortProtect, this);
//   receive_thread_ = std::thread(&StandardRobotPpRos2Node::receiveData, this);
//   send_thread_ = std::thread(&StandardRobotPpRos2Node::sendData, this);
// }
// StandardRobotPpRos2Node::~StandardRobotPpRos2Node()
// {
//   if (send_thread_.joinable()) {
//     send_thread_.join();
//   }

//   if (receive_thread_.joinable()) {
//     receive_thread_.join();
//   }

//   if (serial_port_protect_thread_.joinable()) {
//     serial_port_protect_thread_.join();
//   }

//   if (serial_driver_->port()->is_open()) {
//     serial_driver_->port()->close();
//   }

//   if (owned_ctx_) {
//     owned_ctx_->waitForExit();
//   }
// }

// void StandardRobotPpRos2Node::createPublisher()
// {
//   judge_data_pub_ =
//     this->create_publisher<pb_rm_interfaces::msg::JudgeData>("referee/judge_data", 10);
//   joint_state_pub_ =
//     this->create_publisher<sensor_msgs::msg::JointState>("serial/gimbal_joint_state", 10);
//   // mode_pub =
//     // this->create_publisher<pb_rm_interfaces::msg::JudgeData::mode>("mode", 10);
// }

// void StandardRobotPpRos2Node::createNewDebugPublisher(const std::string & name)
// {
//   RCLCPP_INFO(get_logger(), "Create new debug publisher: %s", name.c_str());
//   std::string topic_name = "serial/debug/" + name;
//   auto debug_pub = this->create_publisher<example_interfaces::msg::Float64>(topic_name, 10);
//   debug_pub_map_.insert(std::make_pair(name, debug_pub));
// }

// void StandardRobotPpRos2Node::createSubscription()
// {
//   cmd_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
//     "cmd_vel", 10,
//     std::bind(&StandardRobotPpRos2Node::cmdVelCallback, this, std::placeholders::_1));
//   cmd_mode_sub_ = this->create_subscription<pb_rm_interfaces::msg::JudgeData>(
//     "referee/judge_data", 10,
//     std::bind(&StandardRobotPpRos2Node::modleCallback, this, std::placeholders::_1));
// }

// void StandardRobotPpRos2Node::getParams()
// {
//   using FlowControl = drivers::serial_driver::FlowControl;
//   using Parity = drivers::serial_driver::Parity;
//   using StopBits = drivers::serial_driver::StopBits;

//   uint32_t baud_rate{};
//   auto fc = FlowControl::NONE;
//   auto pt = Parity::NONE;
//   auto sb = StopBits::ONE;

//   try {
//     device_name_ = declare_parameter<std::string>("device_name", "");
//   } catch (rclcpp::ParameterTypeException & ex) {
//     RCLCPP_ERROR(get_logger(), "The device name provided was invalid");
//     throw ex;
//   }

//   try {
//     baud_rate = declare_parameter<int>("baud_rate", 0);
//   } catch (rclcpp::ParameterTypeException & ex) {
//     RCLCPP_ERROR(get_logger(), "The baud_rate provided was invalid");
//     throw ex;
//   }

//   try {
//     const auto fc_string = declare_parameter<std::string>("flow_control", "");

//     if (fc_string == "none") {
//       fc = FlowControl::NONE;
//     } else if (fc_string == "hardware") {
//       fc = FlowControl::HARDWARE;
//     } else if (fc_string == "software") {
//       fc = FlowControl::SOFTWARE;
//     } else {
//       throw std::invalid_argument{
//         "The flow_control parameter must be one of: none, software, or hardware."};
//     }
//   } catch (rclcpp::ParameterTypeException & ex) {
//     RCLCPP_ERROR(get_logger(), "The flow_control provided was invalid");
//     throw ex;
//   }

//   try {
//     const auto pt_string = declare_parameter<std::string>("parity", "");

//     if (pt_string == "none") {
//       pt = Parity::NONE;
//     } else if (pt_string == "odd") {
//       pt = Parity::ODD;
//     } else if (pt_string == "even") {
//       pt = Parity::EVEN;
//     } else {
//       throw std::invalid_argument{"The parity parameter must be one of: none, odd, or even."};
//     }
//   } catch (rclcpp::ParameterTypeException & ex) {
//     RCLCPP_ERROR(get_logger(), "The parity provided was invalid");
//     throw ex;
//   }
//   try {
//     const auto sb_string = declare_parameter<std::string>("stop_bits", "");

//     if (sb_string == "1" || sb_string == "1.0") {
//       sb = StopBits::ONE;
//     } else if (sb_string == "1.5") {
//       sb = StopBits::ONE_POINT_FIVE;
//     } else if (sb_string == "2" || sb_string == "2.0") {
//       sb = StopBits::TWO;
//     } else {
//       throw std::invalid_argument{"The stop_bits parameter must be one of: 1, 1.5, or 2."};
//     }
//   } catch (rclcpp::ParameterTypeException & ex) {
//     RCLCPP_ERROR(get_logger(), "The stop_bits provided was invalid");
//     throw ex;
//   }

//   device_config_ =
//     std::make_unique<drivers::serial_driver::SerialPortConfig>(baud_rate, fc, pt, sb);

//   record_rosbag_ = declare_parameter("record_rosbag", false);
//   set_detector_color_ = declare_parameter("set_detector_color", false);
//   debug_ = declare_parameter("debug", false);
// }
// /********************************************************/
// /* Serial port protect                                  */
// /********************************************************/
// void StandardRobotPpRos2Node::serialPortProtect()
// {
//   RCLCPP_INFO(get_logger(), "Start serialPortProtect!");

//   // @TODO: 1.保持串口连接 2.串口断开重连 3.串口异常处理

//   // 初始化串口
//   serial_driver_->init_port(device_name_, *device_config_);
//   // 尝试打开串口
//   try {
//     if (!serial_driver_->port()->is_open()) {
//       serial_driver_->port()->open();
//       RCLCPP_INFO(get_logger(), "Serial port opened!");
//       is_usb_ok_ = true;
//     }
//   } catch (const std::exception & ex) {
//     RCLCPP_ERROR(get_logger(), "Open serial port failed : %s", ex.what());
//     is_usb_ok_ = false;
//   }

//   is_usb_ok_ = true;
//   std::this_thread::sleep_for(std::chrono::milliseconds(USB_PROTECT_SLEEP_TIME));

//   while (rclcpp::ok()) {
//     if (!is_usb_ok_) {
//       try {
//         if (serial_driver_->port()->is_open()) {
//           serial_driver_->port()->close();
//         }

//         serial_driver_->port()->open();

//         if (serial_driver_->port()->is_open()) {
//           RCLCPP_INFO(get_logger(), "Serial port opened!");
//           is_usb_ok_ = true;
//         }
//       } catch (const std::exception & ex) {
//         is_usb_ok_ = false;
//         RCLCPP_ERROR(get_logger(), "Open serial port failed : %s", ex.what());
//       }
//     }

//     // thread sleep
//     std::this_thread::sleep_for(std::chrono::milliseconds(USB_PROTECT_SLEEP_TIME));
//   }
// }
// /********************************************************/
// /* Receive data                                         */
// /********************************************************/
// void StandardRobotPpRos2Node::receiveData()
// {
//   RCLCPP_INFO(get_logger(), "Start receiveData!");

//   std::vector<uint8_t> sof(1);
//   std::vector<uint8_t> receive_data;

//   int sof_count = 0;
//   int retry_count = 0;
//   timestamp_offset_ = this->declare_parameter("timestamp_offset", 0.0);
//   tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
//   while (rclcpp::ok()) 
//   {
//     if (!is_usb_ok_) {
//       RCLCPP_WARN(get_logger(), "receive: usb is not ok! Retry count: %d", retry_count++);
//       std::this_thread::sleep_for(std::chrono::milliseconds(USB_NOT_OK_SLEEP_TIME));
//       continue;
//     }

//     try 
//     {
//       serial_driver_->port()->receive(sof);

//       if (sof[0] != SOF_RECEIVE) {
//         sof_count++;
//         RCLCPP_INFO(get_logger(), "Find sof, cnt=%d", sof_count);
//         continue;
//       }
//       // Reset sof_count when SOF_RECEIVE is found
//       sof_count = 0;
//       // sof[0] == SOF_RECEIVE 后读取剩余 header_frame 内容
//       std::vector<uint8_t> header_frame_buf(1);  // sof 在读取完数据后添加
//       serial_driver_->port()->receive(header_frame_buf);  // 读取除 sof 外剩下的数据
//       header_frame_buf.insert(header_frame_buf.begin(), sof[0]);  // 添加 sof
//       HeaderFrame header_frame = fromVector<HeaderFrame>(header_frame_buf);
//       // crc8_ok 校验正确后读取数据段
//       // 根据数据段长度读取数据
//       std::vector<uint8_t> data_buf(header_frame.len );  // len + crc
//       int received_len = serial_driver_->port()->receive(data_buf);
//       int received_len_sum = received_len;
//       // 考虑到一次性读取数据可能存在数据量过大，读取不完整的情况。需要检测是否读取完整
//       // 计算剩余未读取的数据长度
//       int remain_len = header_frame.len  - received_len;
//       while (remain_len > 0) {  // 读取剩余未读取的数据
//         std::vector<uint8_t> remain_buf(remain_len);
//         received_len = serial_driver_->port()->receive(remain_buf);
//         data_buf.insert(data_buf.begin() + received_len_sum, remain_buf.begin(), remain_buf.end());
//         received_len_sum += received_len;
//         remain_len -= received_len;
//       }
//       // 数据段读取完成后添加 header_frame_buf 到 data_buf，得到完整数据包
//       data_buf.insert(data_buf.begin(), header_frame_buf.begin(), header_frame_buf.end());
//       JudgeData judge_data = fromVector<JudgeData>(data_buf);
//       //tian jia 
//       geometry_msgs::msg::TransformStamped t;
//       timestamp_offset_ = this->get_parameter("timestamp_offset").as_double();
//       t.header.stamp = this->now() + rclcpp::Duration::from_seconds(timestamp_offset_);
//       t.header.frame_id = "odom1";
//       t.child_frame_id = "gimbal_link1";
//       auto roll = 0;
//       auto pitch = judge_data.data.pitch * M_PI / 180.0;           
//       auto yaw = judge_data.data.yaw * M_PI / 180.0;
//       tf2::Quaternion q;
//       q.setRPY(roll, pitch, yaw);
//       t.transform.rotation = tf2::toMsg(q);
//       tf_broadcaster_->sendTransform(t);
//       // odom_rectify: 转了roll角后的坐标系
//       Eigen::Quaterniond q_eigen(q.w(), q.x(), q.y(), q.z());
//       Eigen::Vector3d rpy = getRPY(q_eigen.toRotationMatrix());
//       q.setRPY(rpy[0], 0, 0);
//       t.transform.rotation = tf2::toMsg(q);
//       t.header.frame_id = "odom1";
//       t.child_frame_id = "odom1_rectify";
//       tf_broadcaster_->sendTransform(t);
//       //tian jia 
//       publishJudgeData(judge_data);
//     } catch (const std::exception & ex) 
//     {
//       RCLCPP_ERROR(get_logger(), "Error receiving data: %s", ex.what());
//       is_usb_ok_ = false;
//     }
//   }
// }
// void StandardRobotPpRos2Node::publishJudgeData(JudgeData & judgedata)
// {
//   pb_rm_interfaces::msg::JudgeData msg;
//   // pb_rm_interfaces::msg::JudgeData::mode;
//   msg.game_type= judgedata.data.game_type;
//   msg.game_progress= judgedata.data.game_progress;
//   msg.pitch= -judgedata.data.pitch;
//   msg.yaw= judgedata.data.yaw;
//   msg.bullet_speed= judgedata.data.bullet_speed;
//   msg.mode=judgedata.data.mode;
//   judge_data_pub_->publish(msg);
//   // RCLCPP_INFO(get_logger(),"have message:%d",judgedata.data.game_type);
//   std::cout << "Game Type: " << (int)msg.game_type << std::endl;
//   std::cout << "Game Progress: " << (int)msg.game_progress << std::endl;
//   std::cout<<"pitch: "<<(int)msg.pitch<<std::endl;
//   std::cout<<"yaw: "<<(int)msg.yaw<<std::endl;
//   std::cout<<"bullet_speed: "<<(int)msg.bullet_speed<<std::endl;  
//   std::cout<<"mode: "<<(int)msg.mode<<std::endl;
// }
// // void StandardRobotPpRos2Node::publishMode(int & mode)
// // {
// //   pb_rm_interfaces::msg::JudgeData::mode msg;
// //   msg.mode=mode;
// //   mode_pub->publish(msg);
// // }
// /********************************************************/
// /* Send data                                            */
// /********************************************************/
// void StandardRobotPpRos2Node::sendData()
// {
//   RCLCPP_INFO(get_logger(), "Start sendData!");

//   send_robot_cmd_data_.frame_header.sof = SOF_SEND;
//   send_robot_cmd_data_.frame_header.len = 8;
//   send_robot_cmd_data_.data.vx = 0;
//   send_robot_cmd_data_.data.vy = 0;
//   send_robot_cmd_data_.data.wz = 80;
//   send_robot_cmd_data_.data.mode =0;
//   send_robot_cmd_data_.data.pitch =0;
//   send_robot_cmd_data_.data.yaw =0;
//   send_robot_cmd_data_.data.fire_advice = false;

//   int retry_count = 0;

//   while (rclcpp::ok()) {
//     if (!is_usb_ok_) {
//       RCLCPP_WARN(get_logger(), "send: usb is not ok! Retry count: %d", retry_count++);
//       std::this_thread::sleep_for(std::chrono::milliseconds(USB_NOT_OK_SLEEP_TIME));
//       continue;
//     }

//     try {
//       std::vector<uint8_t> send_data = toVector(send_robot_cmd_data_);
//       serial_driver_->port()->send(send_data);
//     } catch (const std::exception & ex) {
//       RCLCPP_ERROR(get_logger(), "Error sending data: %s", ex.what());
//       is_usb_ok_ = false;
//     }
//     std::this_thread::sleep_for(std::chrono::milliseconds(5));
//   }
// }
// void StandardRobotPpRos2Node::cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
// {
//   send_robot_cmd_data_.data.vx = (msg->linear.x)*25;
//   send_robot_cmd_data_.data.vy = (msg->linear.y)*25;
//   send_robot_cmd_data_.data.wz = 100;
// }
// void StandardRobotPpRos2Node::modleCallback(const pb_rm_interfaces::msg::JudgeData::SharedPtr msg)
// {
//   send_robot_cmd_data_.data.mode = msg->mode;
//   if(msg->mode==1)
//   {shijue_sub_1=this->create_subscription<rm_interfaces::msg::GimbalCmd>("armor_solver/cmd_gimbal",
//     rclcpp::SensorDataQoS(),std::bind(&StandardRobotPpRos2Node::aimCallback, this, std::placeholders::_1));}
//   else{
//     if(msg->mode==2||msg->mode==3)
//     {
//       shijue_sub_2=this->create_subscription<rm_interfaces::msg::GimbalCmd>("rune_solver/cmd_gimbal",
//     rclcpp::SensorDataQoS(),std::bind(&StandardRobotPpRos2Node::aimCallback, this, std::placeholders::_1));
//     }
//     else return;
//   }
// }
// void StandardRobotPpRos2Node::aimCallback(const rm_interfaces::msg::GimbalCmd::SharedPtr msg)
// {
//   send_robot_cmd_data_.data.pitch = msg->pitch;
//   send_robot_cmd_data_.data.yaw = msg->yaw;
//   send_robot_cmd_data_.data.fire_advice = msg->fire_advice;
// }
// inline Eigen::Vector3d StandardRobotPpRos2Node::getRPY(const Eigen::Matrix3d &R) {
//   double yaw = atan2(R(0, 1), R(0, 0));
//   double c2 = Eigen::Vector2d(R(2, 2), R(1, 2)).norm();
//   double pitch = atan2(-R(0, 2), c2);
//   double s1 = sin(yaw);
//   double c1 = cos(yaw);
//   double roll = atan2(s1 * R(2, 0) - c1 * R(2, 1), c1 * R(1, 1) - s1 * R(1, 0));
//   return -Eigen::Vector3d(roll, pitch, yaw);
// }
// }
// #include "rclcpp_components/register_node_macro.hpp"
// RCLCPP_COMPONENTS_REGISTER_NODE(standard_robot_pp_ros2::StandardRobotPpRos2Node)
