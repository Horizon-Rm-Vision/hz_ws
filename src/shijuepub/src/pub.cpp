#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;
class pub :public rclcpp::Node
{
    public:
    pub():Node("pub")
    {
        this->declare_parameter("hp",300);
        publisher_=this->create_publisher<std_msgs::msg::String>("hp",10);
        timer_=this->create_wall_timer(
            500ms,std::bind(&pub::timer_callback,this)
        );
    }
    private:
      void timer_callback()
      {
         int hp=this->get_parameter("hp").as_int();
         auto message=std_msgs::msg::String();
         message.data=std::to_string(hp);
         RCLCPP_INFO(this->get_logger(),"publisher:%s",message.data.c_str());
         publisher_->publish(message);
      }
      rclcpp::TimerBase::SharedPtr timer_;
      rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};
int main(int argc,char**argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<pub>());
    rclcpp::shutdown();
    return 0;
}
