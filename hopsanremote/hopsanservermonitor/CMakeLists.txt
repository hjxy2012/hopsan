cmake_minimum_required(VERSION 3.0)
project(HopsanServerMonitor)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_DEBUG_POSTFIX _d)
find_package(Threads REQUIRED)

set(target_name hopsanservermonitor)

add_executable(${target_name} main.cpp)

target_include_directories(${target_name} PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/tclap/include>)

target_link_libraries(${target_name} libhopsanremoteclient libhopsanremotecommon Threads::Threads)

set_target_properties(${target_name} PROPERTIES INSTALL_RPATH "\$ORIGIN/../lib")

install(TARGETS ${target_name}
  RUNTIME DESTINATION bin
)
