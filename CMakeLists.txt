cmake_minimum_required(VERSION 3.16)
project(aurore LANGUAGES C VERSION 1.0.0)

add_executable(socket socket.c)

add_executable(socket_client socket_client.c)