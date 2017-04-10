

find_package(Eigen3 REQUIRED)

IF(EIGEN3_FOUND)
INCLUDE_DIRECTORIES( ${EIGEN3_INCLUDE_DIR} )
ENDIF(EIGEN3_FOUND)

add_subdirectory(beginner_tutorials beginner_tutorials)

