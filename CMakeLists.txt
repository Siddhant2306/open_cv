cmake_minimum_required(VERSION 3.10)
project(OpenCVTest)


set(OpenCV_PATH "C:/Users/Siddhant/Downloads/opencv/build")

include_directories("${OpenCV_PATH}/include")


link_directories("${OpenCV_PATH}/x64/vc16/lib")


add_executable(OpenCVTest main.cpp)


target_link_libraries(OpenCVTest
    debug opencv_world4120d
    optimized opencv_world4120
)
