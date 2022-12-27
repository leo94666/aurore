cmake_minimum_required(VERSION 3.16)
project(aurore LANGUAGES C VERSION 1.0.0)


include_directories(include)


aux_source_directory(src SRC)


add_definitions(-DLOG_USE_COLOR)


add_library(aurore ${SRC})


add_subdirectory(test)