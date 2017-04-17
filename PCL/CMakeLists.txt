find_package(Eigen3 REQUIRED)

IF(EIGEN3_FOUND)
INCLUDE_DIRECTORIES( ${EIGEN3_INCLUDE_DIR} )
ENDIF(EIGEN3_FOUND)

find_package(PCL 1.7 REQUIRED)

#set(PCL_INCLUDE_DIRS "/usr/local/include/pcl-1.8")


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(pcl_write_test pcd_write.cpp)
target_link_libraries(pcl_write_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

add_executable(pcl_transport transport.cpp)
target_link_libraries(pcl_transport ${PCL_LIBRARIES})

add_executable(pcl_visualizer visualizer.cpp)
target_link_libraries(pcl_visualizer ${PCL_LIBRARIES})
