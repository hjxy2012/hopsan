cmake_minimum_required(VERSION 3.0)
project(HopsanServerWorker)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_DEBUG_POSTFIX _d)
find_package(Threads REQUIRED)

set(target_name hopsanserverworker)

add_executable(${target_name} main.cpp)

target_include_directories(${target_name} PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../dependencies/tclap/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../Utilities>)

target_link_libraries(${target_name} libhopsanremotecommon hopsancore Threads::Threads)

set_target_properties(${target_name} PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib")

install(TARGETS ${target_name}
  RUNTIME DESTINATION bin
)
