find_package(Eigen3 REQUIRED)

IF(EIGEN3_FOUND)
INCLUDE_DIRECTORIES( ${EIGEN3_INCLUDE_DIR} )
ENDIF(EIGEN3_FOUND)


add_executable(eigen_matrixAndVertex matrixAndVertex.cpp)
add_executable(eigen_linerSolver linerSolver.cpp)
add_executable(eigen_LGSSolve LGSSolve.cpp)