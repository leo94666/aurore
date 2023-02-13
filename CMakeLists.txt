cmake_minimum_required(VERSION 3.16)
project(aurore VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)


include_directories(inc)
include_directories(include)


aux_source_directory(lib SRC)


add_definitions(-DLOG_USE_COLOR)


add_library(aurore ${SRC})


add_subdirectory(test)