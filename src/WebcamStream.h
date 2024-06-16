#include <opencv2/opencv.hpp>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
class Camera{
  private:
    cv::VideoCapture camera;
    int width{};
    int height{};
    std::string cameraName{};
    std::string pathToCam{};
public:
    cv::Mat getImage();
    Camera(std::string pathToCam,std::string CameraName, int width, int height);

    };

