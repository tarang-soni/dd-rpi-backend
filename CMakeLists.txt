cmake_minimum_required(VERSION 4.1)
project(rpi_backend)

set(CMAKE_CXX_STANDARD 20)

add_executable(rpi_backend
        main.cpp
        Platforms/Windows/WinClientSocket.cpp
        Platforms/Windows/WinClientSocket.h
        TClientSocket.cpp
        TClientSocket.h)
target_include_directories(rpi_backend PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/Windows
)
target_link_libraries(
        rpi_backend PRIVATE ws2_32
)
