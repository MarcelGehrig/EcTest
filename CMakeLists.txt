cmake_minimum_required(VERSION 2.6)
project(ectest)

list(APPEND ADDITIONAL_INCLUDE_DIRS "/home/mgehrig2/projects/023_MyEcMasterDemoDC_ClassA/install/include")
list(APPEND ADDITIONAL_LINK_DIRS "/home/mgehrig2/projects/023_MyEcMasterDemoDC_ClassA/install/lib")
# list(APPEND ADDITIONAL_LINK_DIRS "/home/mgehrig2/projects/020_EtherCAT/EC-Master-V2.9-Linux_x64-Eval/Bin/Linux/x64")

include_directories(${ADDITIONAL_INCLUDE_DIRS})
link_directories(${ADDITIONAL_LINK_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(ectest main.cpp)

target_link_libraries(ectest myecmasterlib pthread)

install(TARGETS ectest RUNTIME DESTINATION bin)




