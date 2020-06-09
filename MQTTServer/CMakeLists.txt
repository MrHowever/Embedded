cmake_minimum_required(VERSION 3.15)
project(MQTTServer C)

set(CMAKE_C_STANDARD 11)

add_executable(MQTTServer main.c)
target_link_libraries(MQTTServer mosquitto)