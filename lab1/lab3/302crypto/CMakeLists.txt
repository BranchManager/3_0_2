cmake_minimum_required(VERSION 3.9)
project(302crypto)

set(CMAKE_CXX_STANDARD 98)

add_executable(302crypto Crypto.cpp support.cpp support.h)