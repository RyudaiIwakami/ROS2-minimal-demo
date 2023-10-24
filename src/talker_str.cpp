// 1.includeヘッダーファイル
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std::chrono_literals;

// 3.ノードのクラスを定義
class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      startFile.open("start_times_ROS2_32byte.txt", std::ios::app);
      // 3-1.publisher生成
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      // 3-2.タイマー生成
      sleep(5);
      timer_ = this->create_wall_timer(50ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      // 3-3.メッセージを作ってpubする
      auto message = std_msgs::msg::String();
      message.data = "1";
      RCLCPP_INFO(this->get_logger(), "Pulish：'%s'", message.data.c_str());
      publisher_->publish(message);
      
      auto start = std::chrono::high_resolution_clock::now();
      auto start_time = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
      startFile << "Run" << std::setw(5) << (time_count_ROS2_start++) << ":" << start_time << std::endl;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
    int time_count_ROS2_start = 0;
    std::ofstream startFile;
};

int main(int argc, char * argv[])
{
  // 2.initial ROS2
  rclcpp::init(argc, argv);
  // 4.オブジェクトポインターの導入、spin():プログラムを終わらせないように保持
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  // 5.資源リリース
  rclcpp::shutdown();
  return 0;
}
