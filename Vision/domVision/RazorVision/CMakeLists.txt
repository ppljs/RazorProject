project(RazorVision)
cmake_minimum_required(VERSION 3.7)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/tmp)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/tmp)

set(DCMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

set(OpenCV_COMPILER_FLAGS "-lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_imgproc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenCV_COMPILER_FLAGS} -lpthread -lrt -lpigpio")

include_directories("${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include/entities"
    "${CMAKE_SOURCE_DIR}/include/entities/vision"
    "${CMAKE_SOURCE_DIR}/include/entities/brain"
    "${CMAKE_SOURCE_DIR}/include/utils"
    "${CMAKE_SOURCE_DIR}/include/constants")

file(GLOB SOURCES
    include/entities/brain/*.hh
    include/entities/vision/*.hh
    include/utils/*
    include/constants/*
    src/*.cpp
    src/utils/*.cc
    src/entities/vision/*.cc
    src/entities/brain/*.cc
    )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Open_CV_LIBS})
