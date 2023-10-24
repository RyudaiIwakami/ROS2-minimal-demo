// 1.includeヘッダーファイル
#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using namespace std::chrono_literals;
using base_interfaces_demo::msg::Student;
// 3.ノードのクラスを定義　
class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("student_publisher"), count_(0)
    {
      // 3-1.publisher生成
      publisher_ = this->create_publisher<Student>("topic_stu", 10);
      // 3-2.タイマー生成
      timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      // 3-3.メッセージを作ってpubする
      auto stu = Student();
      stu.name = "Carlos";
      stu.age = count_++;
      stu.height = 1.82;
      RCLCPP_INFO(this->get_logger(), "stu_info:name=%s,age=%d,height=%.2f", stu.name.c_str(),stu.age,stu.height);
      publisher_->publish(stu);

    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<Student>::SharedPtr publisher_;
    size_t count_;
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
