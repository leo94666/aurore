cmake_minimum_required(VERSION 3.16)
project(aurore LANGUAGES C VERSION 1.0.0)

add_executable(tcp_server tcp_server.c)

add_executable(socket_client tcp_client.c)


add_executable(udp_server udp_server.c)