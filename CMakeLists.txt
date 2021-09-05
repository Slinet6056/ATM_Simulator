cmake_minimum_required(VERSION 3.20)
project(ATM_Simulator)

set(CMAKE_CXX_STANDARD 11)

set(INC_DIR ./include)
set(LINK_DIR ./lib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(ATM_Simulator main.cpp EasyX.cpp EasyX.h Account.cpp Account.h Record.cpp Record.h System.cpp System.h MD5.cpp MD5.h)

target_link_libraries(ATM_Simulator EasyXa EasyXw VSCustomNativeHeapEtwProvider VsGraphicsHelper)