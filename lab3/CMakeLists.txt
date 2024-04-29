cmake_minimum_required(VERSION 3.5.1)
project(lab0_2_3x_eigen_opencv)     #set project name

find_package(OpenCV REQUIRED)
include_directories("/usr/local/include/eigen3")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_compile_options(${PROJECT_NAME} PRIVATE ${compile_options})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON CXX_STANDARD 17)

