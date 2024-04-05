cmake_minimum_required(VERSION 3.0.0)
project(SFUI VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

aux_source_directory(./src SRC)
add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

# Find SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)

add_subdirectory(./test/GoogleLike)
