cmake_minimum_required(VERSION 2.8.9)
project (allocate_ports)
include_directories(/opt/libc++/boost/1.64.0/include)
include_directories(/home/mxiong/googletest/googletest/include)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything -D__UNITTEST__ -pthread")
add_executable(allocate_ports allocate_ports.cpp)

add_executable(allocate_ports_ut allocate_ports.cpp)
target_link_libraries(allocate_ports_ut /home/mxiong/googletest/build/lib/libgtest.a pthread)
set_target_properties(allocate_ports_ut PROPERTIES COMPILE_FLAGS "-D__UNITTEST__")

enable_testing()
add_test(NAME mytest COMMAND allocate_ports_ut)

