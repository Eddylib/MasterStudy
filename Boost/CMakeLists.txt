message(STATUS "boost start")
cmake_minimum_required(VERSION 2.8)

find_package(Boost  COMPONENTS thread system REQUIRED)
message(STATUS Boost_CONFIG: ${Boost_CONFIG} ${BOOST_INCLUDE_DIR})
IF(BOOST_FOUND)
    INCLUDE_DIRECTORIES( ${BOOST_INCLUDE_DIR} )
ENDIF(BOOST_FOUND)


add_compile_options(-std=c++11)

add_executable(boost_thread thread.cpp)
target_link_libraries(boost_thread ${Boost_LIBRARIES})


add_executable(boost_condition condition.cpp)
target_link_libraries(boost_condition ${Boost_LIBRARIES})
message(STATUS "boost end")