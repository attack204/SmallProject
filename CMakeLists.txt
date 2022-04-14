cmake_minimum_required(VERSION 3.21)
project(SmallProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(C++/SmartPointer)

add_executable(SmallProject
        C++/SmartPointer/smart_pointer.cpp
        C++/SmartPointer/smart_pointer.h)
