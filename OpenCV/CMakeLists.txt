find_package(OpenCV REQUIRED)
find_package(Boost  COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

IF(BOOST_FOUND)

    INCLUDE_DIRECTORIES( ${BOOST_INCLUDE_DIR} )

ENDIF(BOOST_FOUND)
include_directories($OpenCV_INCLUDE_DIRS)

message(STATUS ${Boost_LIBRARIES})

add_executable(OpenCV_image_crop crop_image.cpp)
target_link_libraries(OpenCV_image_crop ${OpenCV_LIBS} ${Boost_LIBRARIES})