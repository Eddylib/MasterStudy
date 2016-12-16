cmake_policy(VERSION 2.8)

project(trait_sill)

cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++11)
include_directories(./include)
link_directories(./lib)

add_executable(main ./src/main_traits.cpp)
