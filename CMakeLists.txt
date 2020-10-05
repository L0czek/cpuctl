cmake_minimum_required(VERSION 3.0)

project(cpuctl CXX)
set(CMAKE_CXX_STANDARD 20)
find_package(Boost REQUIRED)
include_directories(inc ${Boost_INCLUDE_DIRS})

add_executable(cpuctl
    inc/cpuctl.hpp
    inc/ioctl.h

    src/cpuctl.cc
    src/main.cc
)

install(TARGETS cpuctl DESTINATION bin)
install(FILES config.ini DESTINATION /etc/cpuctl)
install(FILES cpuctl.service DESTINATION /etc/systemd/system/)
