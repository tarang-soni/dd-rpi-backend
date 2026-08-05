//
// Created by sonit on 05-08-2026.
//

#ifndef RPI_BACKEND_VIDEOSTREAMER_H
#define RPI_BACKEND_VIDEOSTREAMER_H
#include <gst/gst.h>
#include <string>
namespace dd_rpi_backend
{
    class VideoStreamer
    {
    public:
        VideoStreamer();
        ~VideoStreamer();

        bool start(const std::string& pipelineIp,int port);
        void stop();

    private:
        GstElement *pipeline;
    };
}
#endif //RPI_BACKEND_VIDEOSTREAMER_H