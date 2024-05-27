cmake_minimum_required(VERSION 3.25.1)
project(temp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

#find_package(Boost REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)

if(MSVC)
  #target_compile_options(${PROJECT_NAME}  PRIVATE /W4 /WX)
  add_compile_options(/W4 /WX)
else()
  #target_compile_options(${PROJECT_NAME}  PRIVATE -Wall -Wextra -Wpedantic -Werror)
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
 


