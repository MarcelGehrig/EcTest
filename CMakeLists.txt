cmake_minimum_required(VERSION 2.6)
project(ectest)

add_executable(ectest main.cpp)

install(TARGETS ectest RUNTIME DESTINATION bin)
