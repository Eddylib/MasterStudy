find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost  COMPONENTS system filesystem REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(EIGEN3_FOUND)
    INCLUDE_DIRECTORIES( ${EIGEN3_INCLUDE_DIR} )
ENDIF(EIGEN3_FOUND)



IF(BOOST_FOUND)

    INCLUDE_DIRECTORIES( ${BOOST_INCLUDE_DIR} )

ENDIF(BOOST_FOUND)
include_directories($OpenCV_INCLUDE_DIRS)


add_executable(SLAM_base_directMethod directMethod.cpp)
target_link_libraries(SLAM_base_directMethod ${Boost_LIBRARIES} )