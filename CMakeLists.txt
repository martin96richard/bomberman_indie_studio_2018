cmake_minimum_required(VERSION 2.6)
project(bomberman)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/includes
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

set(IRRKLANG_LIBRARY libIrrKlang.so)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/linux)
set(IRRLICHT_LIBRARY
  -L./lib/linux
  -lIrrlicht
  -lX11
  -lXxf86vm
  -lGL
  -pthread
  )

file(GLOB SRCS src/*.cpp)
file(GLOB HRCS src/*.hpp)

add_executable(bomberman
  ${SRCS}
  ${HRCS}
  )

target_link_libraries(bomberman
  ${IRRKLANG_LIBRARY}
  ${IRRLICHT_LIBRARY}
  )
