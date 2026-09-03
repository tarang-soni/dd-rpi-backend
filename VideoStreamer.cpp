//
// Created by sonit on 05-08-2026.
//

#include "VideoStreamer.h"

#include <iostream>
#include <ostream>

dd_rpi_backend::VideoStreamer::VideoStreamer():pipeline(nullptr)
{
    //init gst
    if (!gst_is_initialized())
    {
        gst_init(nullptr, nullptr);
    }
}

dd_rpi_backend::VideoStreamer::~VideoStreamer()
{
    stop();
}

bool dd_rpi_backend::VideoStreamer::start(const std::string& clientIp, int port)
{
    if (pipeline != nullptr)
    {
        std::cerr << "Stream is already running..." << std::endl;
        return true;
    }

    std::string pipelineString;

#if defined(_WIN32) || defined(_WIN64)

    pipelineString =
        "mfvideosrc ! "
        "videoconvert ! "
        "video/x-raw,width=640,height=480,framerate=30/1 ! "
        "x264enc tune=zerolatency ! "
        "rtph264pay config-interval=1 ! "
        "udpsink host=" + clientIp +
        " port=" + std::to_string(port) +
        " sync=false";

#elif defined(__linux__)

    pipelineString =
    "libcamerasrc ! "
    "video/x-raw,width=640,height=480,framerate=15/1 ! "
    "jpegenc quality=60 ! "
    "rtpjpegpay pt=26 ! "
    "udpsink host=" + clientIp +
    " port=" + std::to_string(port) +
    " sync=false async=false";

#else
#error Unsupported platform
#endif

    GError *gerr = nullptr;
    pipeline = gst_parse_launch(pipelineString.c_str(), &gerr);

    if (gerr != nullptr)
    {
        std::cerr << "Failed to parse pipeline: "
                  << gerr->message << std::endl;
        g_error_free(gerr);
        return false;
    }

    GstStateChangeReturn ret =
        gst_element_set_state(pipeline, GST_STATE_PLAYING);

    if (ret == GST_STATE_CHANGE_FAILURE)
    {
        std::cerr << "Camera or encoder failed to start." << std::endl;
        stop();
        return false;
    }

    std::cout << "Streaming started to "
              << clientIp << ":" << port << std::endl;

    return true;
}

void dd_rpi_backend::VideoStreamer::stop()
{
    if (pipeline!=nullptr)
    {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        pipeline=nullptr;
        std::cout<<"Streaming stopped safely."<<std::endl;
    }
    //set state to null
    //remove string ref from gst

}
