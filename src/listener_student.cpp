// 1.includeヘッダーファイル
#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using std::placeholders::_1;
using base_interfaces_demo::msg::Student;
// 3.ノードのクラスを定義
class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("student_subscriber")
    {
      // 3-1.subscriber生成
      subscription_ = this->create_subscription<Student>("topic_stu", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    // 3-2.subしたメッセージの処理
    void topic_callback(const Student & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "rec_stu_info：name=%s,age=%d,height=%.2f", msg.name.c_str(),msg.age, msg.height);
    }
    rclcpp::Subscription<Student>::SharedPtr subscription_;
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
