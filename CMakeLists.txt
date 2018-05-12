cmake_minimum_required(VERSION 2.8)

project (nflb)
set(CMAKE_BUILD_TYPE Release)

add_library(nflb SHARED nflb.c)
