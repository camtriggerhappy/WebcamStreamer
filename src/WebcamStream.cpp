#include <cstdio>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

#include "WebcamStream.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class CameraPublisher : public rclcpp::Node
{
public:
    Camera *camera;
    CameraPublisher() : Node("Camera")
    {
        this->declare_parameter("width", rclcpp::PARAMETER_INTEGER);
        this->declare_parameter("fps", rclcpp::PARAMETER_INTEGER); // we invert this to get the period between image publishes
        this->declare_parameter("camera_path", rclcpp::PARAMETER_STRING);
        this->declare_parameter("camera_name", rclcpp::PARAMETER_STRING);

        camera = new Camera(this->get_parameter("camera_path").as_string(), this->get_parameter("camera_name").as_string(),
                            this->get_parameter("width").as_int(), this->get_parameter("height").as_int());
        auto timer = this->create_wall_timer(std::chrono::milliseconds(static_cast<int>(1 / this->get_parameter("fps").as_double()) * 1000), std::bind(&CameraPublisher::publishImage, this));
    }

    ~CameraPublisher()
    {
        delete camera;
    }
    void publishImage()
    {
        std_msgs::msg::Header header;
        header.stamp = this->now();

        cv_bridge::CvImage image(std_msgs::msg::Header(), "bgr8", this->camera->getImage());
    }
};
cv::Mat Camera::getImage()
{

    cv::Mat image{};
    camera >> image;
}
Camera::Camera(std::string pathToCam, std::string cameraName, int width, int height)
{
    camera = cv::VideoCapture(pathToCam);
};

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraPublisher>());
    rclcpp::shutdown();
    return 0;
}
