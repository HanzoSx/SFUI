cmake_minimum_required(VERSION 3.5.0)
project(SFUI VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE SRC "src/*.cpp")
add_library(SFUI_static STATIC ${SRC})
add_library(SFUI_shared SHARED ${SRC})

set_target_properties(SFUI_static PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    OUTPUT_NAME "SFUI"
)
set_target_properties(SFUI_shared PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    OUTPUT_NAME "SFUI"
)

target_include_directories(SFUI_static PUBLIC include)
target_include_directories(SFUI_shared PUBLIC include)

# Find SFML
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)
target_link_libraries(SFUI_static PUBLIC SFML::Graphics SFML::Window SFML::System)
target_link_libraries(SFUI_shared PUBLIC SFML::Graphics SFML::Window SFML::System)

add_subdirectory(test)
