// 1.includeヘッダーファイル
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>

using std::placeholders::_1;
    std::ofstream endFile;
    int time_count_ROS2_end = 0;
// 3.ノードのクラスを定義
class MinimalSubscriber : public rclcpp::Node
{

  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      // 3-1.subscriber生成
      endFile.open("end_times_ROS2_1byte.txt", std::ios::app);
      subscription_ = this->create_subscription<std_msgs::msg::String>("RETURN", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
  
    // 3-2.subしたメッセージの処理
    void topic_callback(const std_msgs::msg::String & msg) const
    {
      auto end = std::chrono::high_resolution_clock::now();
      auto end_time = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();
      // endFile.open("end_times_ROS2.txt", std::ios::app);
      endFile << "Run" << std::setw(5) << (time_count_ROS2_end++) << ":" << end_time << std::endl;
      RCLCPP_INFO(this->get_logger(), "Subscribe： '%s'", msg.data.c_str());
    }
    
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;


};

int main(int argc, char * argv[])
{
  // 2.initial ROS2
  rclcpp::init(argc, argv);
  // 4.オブジェクトポインターの導入、spin():プログラムを終わらせないように保持
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  // 5.資源リリース
  rclcpp::shutdown();
  return 0;
}
