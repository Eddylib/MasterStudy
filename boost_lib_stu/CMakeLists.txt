project(boost_lib_stu)
cmake_minimum_required(VERSION 2.8)

include_directories(/usr/include)
link_directories(/usr/lib)
find_package(Boost REQUIRED)

#if(NOT Boost_FOUND)
#    message("boost not found")
#else(Boost_FOUND)
#    message("boost found")
#endif()

aux_source_directory(. SRC_LIST)
add_executable(thread thread.cpp)
target_link_libraries(thread boost_thread boost_system)
