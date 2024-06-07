cmake_minimum_required(VERSION 3.20.0)
project(HackerRank LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/../Utils)
add_subdirectory(src)
 