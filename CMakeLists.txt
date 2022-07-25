cmake_minimum_required(VERSION 3.22)
project(AzulLib)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_ROOT "../SFML-2.5.1")
    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
    set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")
    set(SFML_STATIC_LIBRARIES TRUE)
elseif(APPLE)
    set (SFML_ROOT "/opt/homebrew/Cellar/sfml/2.5.1_1")
    set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake/SFML")
    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
    set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")
endif()

set(EAGLES_INCLUDE_DIR "../EaglesLib/include")
set(EAGLES_LIBRARY_DIR "../EaglesLib/lib")

include_directories(${SFML_INCLUDE_DIR} ${EAGLES_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR} ${EAGLES_LIBRARY_DIR})

find_package(SFML 2.5.1 COMPONENTS system window graphics)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

add_library(azul src/AzulWindow.cpp
                 src/AzulCell.cpp
                 src/AzulWorld.cpp
                 src/Azul.cpp
                 src/AzulSteeplechase.cpp
                 src/AzulStep.cpp
                 src/AzulBasic.cpp
                 src/AzulGradLines.cpp
                 src/AzulTicTacToe.cpp )

configure_file(resources/azul.png azul.png COPYONLY)
configure_file(resources/cap.png cap.png COPYONLY)
configure_file(resources/RobotoMono-Regular.ttf RobotoMono-Regular.ttf COPYONLY)
