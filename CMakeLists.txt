cmake_minimum_required(VERSION 4.1)
project(rpi_backend)

set(CMAKE_CXX_STANDARD 20)

add_executable(rpi_backend
        main.cpp
        Platforms/Windows/WinClientSocket.cpp
        Platforms/Windows/WinClientSocket.h
        TClientSocket.cpp
        TClientSocket.h
        Application.cpp
        Application.h
        CommandListener.cpp
        CommandListener.h
        NetworkManager.cpp
        NetworkManager.h
        Protocols.h
        VideoStreamer.cpp
        VideoStreamer.h
)
target_include_directories(rpi_backend PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/Windows
)
if(WIN32)
    target_link_libraries(rpi_backend PRIVATE ws2_32)

    # Location of GStreamer .pc files
    set(ENV{PKG_CONFIG_PATH}
            "D:/Dev/Environments/GStreamer/1.0/mingw_x86_64/lib/pkgconfig")
endif()
find_package(PkgConfig REQUIRED)

pkg_check_modules(GST REQUIRED
        gstreamer-1.0
        gstreamer-video-1.0
)

target_include_directories(rpi_backend PRIVATE
        ${GST_INCLUDE_DIRS}
)

target_compile_options(rpi_backend PRIVATE
        ${GST_CFLAGS_OTHER}
)

target_link_directories(rpi_backend PRIVATE
        ${GST_LIBRARY_DIRS}
)

target_link_libraries(rpi_backend PRIVATE
        ${GST_LIBRARIES}
)