

#set(PCL_ROOT "/usr/local/share/pcl-1.8")

find_package(Eigen3 REQUIRED)

IF(EIGEN3_FOUND)
INCLUDE_DIRECTORIES( ${EIGEN3_INCLUDE_DIR} )
ENDIF(EIGEN3_FOUND)

find_package(PCL 1.8 REQUIRED)

set(PCL_INCLUDE_DIRS "/usr/local/include/pcl-1.8")


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(pcd_write_test pcd_write.cpp)
target_link_libraries(pcd_write_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})

add_executable(transport transport.cpp)
target_link_libraries(transport ${PCL_LIBRARIES})

add_executable(visualizer visualizer.cpp)
target_link_libraries(visualizer ${PCL_LIBRARIES})
