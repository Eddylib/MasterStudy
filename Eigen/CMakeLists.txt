
set (EIGEN3_INCLUDE_DIR "/usr/local/include/eigen3")

find_package(Eigen3 REQUIRED)

IF(EIGEN3_FOUND)
INCLUDE_DIRECTORIES( ${EIGEN3_INCLUDE_DIR} )
ENDIF(EIGEN3_FOUND)


add_executable(matrixAndVertex matrixAndVertex.cpp)
add_executable(linerSolver linerSolver.cpp)
