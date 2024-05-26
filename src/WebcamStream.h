#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/sensor_msgs/msg/image.hpp"
class CameraPublisher : public rclcpp::Node{
  private:
    cv::VideoCapture camera;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr  publisher_ = this->create_publisher<sensor_msgs::msg::Image>("ImageFeed", 10);
public:
    void publishImage();

    };