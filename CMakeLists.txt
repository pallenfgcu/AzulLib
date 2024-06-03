cmake_minimum_required(VERSION 3.24)
project(Azul LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_library(azul
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

# for CMAKE_INSTALL_INCLUDEDIR definition
include(GNUInstallDirs)

target_include_directories(azul
    PRIVATE
        # where the library looks for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
    PUBLIC
        # where library looks for its public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects look for lib's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(azul PRIVATE sfml-graphics)
target_compile_features(azul PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET azul
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:azul>
        VERBATIM)
endif()

install(TARGETS azul)
