cmake_minimum_required(VERSION 2.8)


find_package(Boost  COMPONENTS thread system REQUIRED)

IF(BOOST_FOUND)

    INCLUDE_DIRECTORIES( ${BOOST_INCLUDE_DIR} )

ENDIF(BOOST_FOUND)


add_compile_options(-std=c++11)

add_executable(thread thread.cpp)
target_link_libraries(thread ${Boost_LIBRARIES} )
