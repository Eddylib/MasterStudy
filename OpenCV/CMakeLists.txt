message(STATUS Opencv Begin)



set(OpenCV_DIR /home/libaoyu/Desktop/slam/dependlib/opencv-2.4.9/distdir/usr/local/share/OpenCV)
find_package(OpenCV REQUIRED)
find_package(Boost  COMPONENTS system filesystem REQUIRED QUIET)
message(STATUS OpenCV_CONFIG:${OpenCV_CONFIG})
message(STATUS CMAKE_SYSROOT:${CMAKE_SYSROOT})
message(STATUS CMAKE_ROOT:${CMAKE_ROOT})
message(STATUS CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(BOOST_FOUND)

    INCLUDE_DIRECTORIES( ${BOOST_INCLUDE_DIR} )

ENDIF(BOOST_FOUND)
include_directories($OpenCV_INCLUDE_DIRS)

add_executable(OpenCV_image_crop crop_image.cpp)
target_link_libraries(OpenCV_image_crop ${OpenCV_LIBS} ${Boost_LIBRARIES})
message(STATUS Opencv END)