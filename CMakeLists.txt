cmake_minimum_required(VERSION 3.21)
project(snakeproject)

add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_20)
set(CMAKE_CXX_STANDARD 20)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 REQUIRED graphics network audio window system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(snake WIN32 Snake.cpp)
target_link_libraries(snake PUBLIC default sfml-audio sfml-graphics sfml-window sfml-system)


enable_testing()
add_subdirectory(doctest)

add_executable(snakeproject_snake_test snake_test/test.cpp)
target_link_libraries(snakeproject_snake_test PUBLIC doctest sfml-audio sfml-graphics sfml-window sfml-system)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/openal32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

