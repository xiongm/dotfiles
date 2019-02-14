cmake_minimum_required(VERSION 2.8.9)
project (test)
include_directories(/opt/libc++/boost/1.64.0/include)
include_directories(/home/mxiong/googletest/googletest/include)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything -D__UNITTEST__ -pthread")
add_executable(test allocate_ports.cpp)

add_executable(test_ut allocate_ports.cpp)
target_link_libraries(test_ut /home/mxiong/googletest/build/lib/libgtest.a pthread)
set_target_properties(test_ut PROPERTIES COMPILE_FLAGS "-D__UNITTEST__")

