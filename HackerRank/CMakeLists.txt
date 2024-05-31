cmake_minimum_required(VERSION 3.20.0)
project(HackerRank LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/../Utils)

add_subdirectory(src)

#if(MSVC)
#  target_compile_options(${PROJECT_NAME}  PRIVATE /W4 /WX)
#else()
#  target_compile_options(${PROJECT_NAME}  PRIVATE -Wall -Wextra -Wpedantic -Werror)
#endif()



 
