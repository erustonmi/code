cmake_minimum_required(VERSION 3.16.3)
project(Calendar VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if ( UNIX )
set( CMAKE_CXX_FLAGS_DEBUG_INIT "-fstack-protector" )
elseif( WIN32 )
set( CMAKE_CXX_FLAGS_DEBUG_INIT "/GS" )
endif()

add_executable(dfs main.cpp)
