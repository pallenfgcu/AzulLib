cmake_minimum_required(VERSION 3.24)

project(AzulLib
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# ---- Dependencies ----
include(FetchContent)

# Turn off SFML extras to speed up builds for students
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)

FetchContent_MakeAvailable(SFML)

# ---- AzulLib library ----
add_library(AzulLib
        src/Azul.cpp
        src/AzulBoard.cpp
        src/AzulCell.cpp
        src/AzulWindow.cpp
        src/AzulDrawableCell.cpp
        src/AzulUtility.cpp
        src/Slider.cpp
        src/RoundedRectangleShape.cpp
        src/AnimatedButton.cpp
)

# Modern alias target for consumers
add_library(Azul::AzulLib ALIAS AzulLib)

target_compile_features(AzulLib PUBLIC cxx_std_17)

include(GNUInstallDirs)

target_include_directories(AzulLib
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# If AzulLib headers expose SFML types, this should be PUBLIC (recommended)
target_link_libraries(AzulLib PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)

# ---- Runtime dependencies (Windows) ----
if(WIN32)
    add_custom_command(
            TARGET AzulLib POST_BUILD
            COMMENT "Copy OpenAL DLL for SFML"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
            "$<TARGET_FILE_DIR:AzulLib>"
            VERBATIM
    )
endif()

# ---- Install (optional, but future-proof) ----
install(TARGETS AzulLib)
