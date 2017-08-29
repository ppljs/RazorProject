cmake_minimum_required(VERSION 2.8)

project(RazorProject)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(razor "main.cpp")
target_link_libraries( ${PROJECT_NAME} ${Open_CV_LIBS} )
