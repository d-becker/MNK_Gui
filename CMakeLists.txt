cmake_minimum_required (VERSION 2.8)

project(MNK_Gui)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g -Wall")

set(CPACK_SOURCE_IGNORE_FILES "bin;.*~;")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
