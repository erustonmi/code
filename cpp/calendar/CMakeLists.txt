cmake_minimum_required(VERSION 3.16.3)
project(Calendar VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if ( UNIX )
set( CMAKE_CXX_FLAGS_DEBUG_INIT "-fstack-protector" )
elseif( WIN32 )
set( CMAKE_CXX_FLAGS_DEBUG_INIT "/GS" )
endif()

add_subdirectory(src)
add_executable(calendarSolver main.cpp)
add_subdirectory(test)

target_link_libraries(calendarSolver PUBLIC calendar)
target_include_directories(calendarSolver PUBLIC)
