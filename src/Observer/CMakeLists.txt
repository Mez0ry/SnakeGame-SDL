cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(Observer_Headers Observer.hpp ObserverEvents.hpp)

set(ObserverSubject ${CMAKE_CURRENT_SOURCE_DIR}/Subject/Subject.hpp  ${CMAKE_CURRENT_SOURCE_DIR}/Subject/Subject.cpp)

add_executable(Observer ${Observer_Headers} ${ObserverSubject})
target_include_directories(Observer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Observer PROPERTIES LINKER_LANGUAGE CXX)