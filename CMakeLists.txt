cmake_minimum_required(VERSION 3.20)

project(AzulLib
        VERSION 1.0.1
        DESCRIPTION "Azul's World core library (SFML-based)"
        LANGUAGES CXX
)

include(GNUInstallDirs)

# -----------------------------
# Diagnostics
# -----------------------------
message(STATUS "AzulLib: CMake ${CMAKE_VERSION}")
message(STATUS "AzulLib: Generator: ${CMAKE_GENERATOR}")
message(STATUS "AzulLib: Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "AzulLib: Version: ${PROJECT_VERSION}")

# -----------------------------
# C++ settings
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------
# Library target
# -----------------------------
add_library(AzulLib STATIC)

# Namespaced alias for consumers (recommended)
add_library(Azul::AzulLib ALIAS AzulLib)

# Source files
file(GLOB_RECURSE AZULLIB_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

target_sources(AzulLib PRIVATE ${AZULLIB_SOURCES})

# Public headers are under include/
target_include_directories(AzulLib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(AzulLib PUBLIC cxx_std_17)

# -----------------------------
# SFML dependency
# -----------------------------
# Expect SFML targets to be provided by the parent project (Azul).
# If someone builds AzulLib standalone, they can still use find_package(SFML ...)
# or extend this to FetchContent SFML.
set(_AZULLIB_HAVE_SFML_TARGETS OFF)
if (TARGET sfml-graphics AND TARGET sfml-window AND TARGET sfml-system)
    set(_AZULLIB_HAVE_SFML_TARGETS ON)
endif()

if (NOT _AZULLIB_HAVE_SFML_TARGETS)
    message(FATAL_ERROR
            "AzulLib: SFML targets not found (sfml-graphics/sfml-window/sfml-system).\n"
            "This project is typically built as a dependency of the Azul executable project,\n"
            "which fetches SFML via FetchContent.\n\n"
            "If building AzulLib standalone, provide SFML targets before configuring AzulLib."
    )
endif()

target_link_libraries(AzulLib
        PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)

# -----------------------------
# Install (optional, but clean)
# -----------------------------
install(TARGETS AzulLib
        EXPORT AzulLibTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT AzulLibTargets
        NAMESPACE Azul::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AzulLib
)
