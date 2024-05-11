cmake_minimum_required( VERSION 3.5.1 )

project(lab_1_2_geometry)

  
# Find libraries
list(APPEND CMAKE_MODULE_PATH "/home/yufaye/work/cv/geographiclib/cmake")
# message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(OpenCV 4.9.0 REQUIRED)
find_package(Sophus REQUIRED)
find_package(GeographicLib REQUIRED)
find_package(fmt REQUIRED)
set (FMT_LIBRARIES fmt::fmt)
include_directories(/usr/local/include/eigen3)


add_executable(${PROJECT_NAME}
  main.cpp
  attitude.h
  attitude.cpp
  cartesian_position.h
  cartesian_position.cpp
  dataset.h
  dataset.cpp
  geodetic_position.h
  geodetic_position.cpp
  intrinsics.h
  intrinsics.cpp
  lab_1_2.h
  lab_1_2.cpp
  local_coordinate_system.h
  local_coordinate_system.cpp
  perspective_camera_model.h
  perspective_camera_model.cpp
  viewer_3d.h
  viewer_3d.cpp
  )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${GeographicLib_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Sophus_LIBRARIES} fmt)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${fmt_LIBS})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${sophus_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${compiler_options})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON CXX_STANDARD 17)
