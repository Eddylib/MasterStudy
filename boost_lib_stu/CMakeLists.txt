project(boost_lib_stu)
cmake_minimum_required(VERSION 2.8)

include_directories(/usr/include)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu)
find_package(Boost REQUIRED)


add_compile_options(-std=c++11)

aux_source_directory(. SRC_LIST)
add_executable(thread thread.cpp)
target_link_libraries(thread boost_thread boost_system)
