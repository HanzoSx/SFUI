project(SFUI_GOOGLELIKE VERSION 0.1.0 LANGUAGES C CXX)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

unset(SRC)
aux_source_directory(./src SRC)
add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../include)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)
# target_link_libraries(${PROJECT_NAME} PUBLIC /home/hanzosx/workspace/SFUI/bin/SFUI)
