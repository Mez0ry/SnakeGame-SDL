cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CSDLContext_Sources CSDLContext.cpp)
set(CSDLContext_Headers CSDLContext.hpp)

add_executable(CSDLContext ${CSDLContext_Sources} ${CSDLContext_Headers})
target_include_directories(CSDLContext PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CSDLContext PROPERTIES LINKER_LANGUAGE CXX)