project(MasterStudy)
cmake_minimum_required(VERSION 2.8)

MESSAGE(STATUS "MasterStudy Beginning...")

add_subdirectory(Eigen Eigen)
add_subdirectory(Boost Boost)
add_subdirectory(traitCPP traitCPP)
add_subdirectory(kalmanFilterMatlab kalmanFilterMatlab)
add_subdirectory(Sophus Sophus)
add_subdirectory(PCL PCL)
add_subdirectory(linuxEnviroment linuxEnviroment)
add_subdirectory(ROS ROS)
add_subdirectory(OpenCV OpenCV)

MESSAGE(STATUS "MasterStudy End...")
