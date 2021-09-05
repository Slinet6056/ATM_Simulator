cmake_minimum_required(VERSION 3.20)
project(ATM_Simulator)

set(CMAKE_CXX_STANDARD 11)

set(INC_DIR ./include)
set(LINK_DIR ./lib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(ATM_Simulator main.cpp EasyX.cpp EasyX.h Account.cpp Account.h)

target_link_libraries(ATM_Simulator EasyXa EasyXw VSCustomNativeHeapEtwProvider VsGraphicsHelper)