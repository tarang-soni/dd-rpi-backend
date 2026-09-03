cmake_minimum_required(VERSION 3.20)

project(rpi_backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------
# Platform specific sources
# ----------------------------------------------------------

set(PLATFORM_SOURCES)
set(PLATFORM_INCLUDE_DIRS)

if(WIN32)

    list(APPEND PLATFORM_SOURCES
            Platforms/Windows/WinClientSocket.cpp
            Platforms/Windows/WinClientSocket.h
    )

    list(APPEND PLATFORM_INCLUDE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/Windows
    )

elseif(UNIX)

    list(APPEND PLATFORM_SOURCES
            Platforms/Linux/LinuxClientSocket.cpp
            Platforms/Linux/LinuxClientSocket.h
    )

    list(APPEND PLATFORM_INCLUDE_DIRS
            ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/Linux
    )

endif()

# ----------------------------------------------------------
# Executable
# ----------------------------------------------------------

add_executable(rpi_backend
        main.cpp

        TClientSocket.cpp
        TClientSocket.h

        Application.cpp
        Application.h

        CommandListener.cpp
        CommandListener.h

        NetworkManager.cpp
        NetworkManager.h

        VideoStreamer.cpp
        VideoStreamer.h

        Protocols.h

        ${PLATFORM_SOURCES}
)

# ----------------------------------------------------------
# Include directories
# ----------------------------------------------------------

target_include_directories(rpi_backend PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PLATFORM_INCLUDE_DIRS}
)

# ----------------------------------------------------------
# Windows libraries
# ----------------------------------------------------------

if(WIN32)

    target_link_libraries(rpi_backend PRIVATE ws2_32)

    # Windows GStreamer installation
    set(ENV{PKG_CONFIG_PATH}
            "D:/Dev/Environments/GStreamer/1.0/mingw_x86_64/lib/pkgconfig")

endif()

# ----------------------------------------------------------
# GStreamer
# ----------------------------------------------------------

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