cmake_minimum_required(VERSION 2.8)

project( color )

find_package( OpenCV REQUIRED )
find_package( Qt COMPONENTS REQUIRED )

add_executable( color color.cpp )
target_link_libraries( color ${OpenCV_LIBS} ${Qt_LIBS} )
