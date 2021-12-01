#ifndef __GSCAM_GSCAM_H
#define __GSCAM_GSCAM_H

extern "C"{
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
}

#include <rclcpp/rclcpp.hpp>

#include <image_transport/image_transport.hpp>
#include <camera_info_manager/camera_info_manager.hpp>

#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/srv/set_camera_info.hpp>

#include <stdexcept>

namespace gscam {

  class GSCam : public rclcpp::Node {
  public:
    GSCam(const rclcpp::NodeOptions &options);
    ~GSCam();

  private:
    bool configure();
    bool init_stream();
    void publish_stream();
    void cleanup_stream();
    static void triggering(std::shared_ptr<rclcpp::Node> node_ptr, double frame_rate, double phase, int gpio_pin);

    void run();

    // General gstreamer configuration
    std::string gsconfig_;

    // Gstreamer structures
    GstElement *pipeline_;
    GstElement *sink_;

    // Appsink configuration
    bool sync_sink_;
    bool preroll_;
    bool reopen_on_eof_;
    bool use_gst_timestamps_;

    // Camera publisher configuration
    std::string frame_id_;
    int width_, height_;
    std::string image_encoding_;
    std::string camera_name_;
    std::string camera_info_url_;

    // Triggering configuration
    double frame_rate_;
    double phase_;
    int gpio_;
    bool use_triggering_;

    // ROS Inteface
    // Calibration between ros::Time and gst timestamps
    double gst_time_offset_;
    // Offset from shutter to receive in gst
    double recv_time_offset_;
    camera_info_manager::CameraInfoManager camera_info_manager_;
    image_transport::CameraPublisher camera_pub_;
    // Case of a jpeg only publisher
    rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr jpeg_pub_;
    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr cinfo_pub_;

    // Poll gstreamer on a separate thread
    std::thread pipeline_thread_;
  };

}

#endif // ifndef __GSCAM_GSCAM_H
