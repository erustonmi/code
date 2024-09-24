add_executable(blockTest block.t.cpp)

if ( UNIX )
set( CMAKE_CXX_FLAGS_DEBUG_INIT "-fstack-protector" )
elseif( WIN32 )
set( CMAKE_CXX_FLAGS_DEBUG_INIT "/GS" )
endif()
# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(blockTest
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(blockTest PUBLIC calendar)
