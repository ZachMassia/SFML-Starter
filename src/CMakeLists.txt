cmake_minimum_required(VERSION 2.8)

# SFML
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Thor
find_package(Thor 2 REQUIRED)
include_directories(${THOR_INCLUDE_DIR})

# Update LIBS variable
set(LIBS ${LIBS}
    ${SFML_LIBRARIES}
    ${THOR_LIBRARY}
)

set(SRC_FILES
    gameengine.h
    gameengine.cpp
    gamestate.h
    introstate.h
    introstate.cpp
    playstate.h
    playstate.cpp
    menustate.h
    menustate.cpp
)

add_library(src ${SRC_FILES})

target_link_libraries(src ${LIBS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
