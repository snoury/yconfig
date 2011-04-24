cmake_minimum_required(VERSION 2.6)

project(yconfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
find_package(YamlCpp REQUIRED)
include_directories(${YAMLCPP_INCLUDE_DIR} include)
link_directories(${YAMLCPP_LIBRARY_DIR})

file(GLOB_RECURSE TEST_FILES tests/*)
file(GLOB_RECURSE SOURCE_FILES src/*)
file(GLOB_RECURSE INCLUDE_FILES include/*)

add_library(yconfig SHARED include/Config.h src/Config.cpp)
target_link_libraries(yconfig ${YAMLCPP_LIBRARY})

add_executable(configtest tests/configtest.cpp)
target_link_libraries(configtest yconfig)

# ${YAMLCPP_LIBRARY})
