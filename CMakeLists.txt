cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(BasiCppMSA VERSION 0.1 LANGUAGES CXX)
set(PROJECT_NAME_L basicppmsa)

# -----------------------------------------------------------------------------
# Build settings
# -----------------------------------------------------------------------------

# Set the C standard
# ------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set the C++ standard
# --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
# -------
OPTION(BUILD_SHARED_LIBS OFF "Build shared libraries")
OPTION(BUILD_TESTS ON "Build the testing tree")
OPTION(BUILD_SAMPLES ON "Build the sample application")
OPTION(ENABLE_CODECOV OFF "Enable code coverage reporting")

# Include additional cmake/ settings
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

include(BuildType)
include(BuildLocation)
include(CompilerFlags)

# -----------------------------------------------------------------------------
# Create and set target properties
# -----------------------------------------------------------------------------
message(STATUS "Setting target properties")

# Set the library sources
# -----------------------
set(libsrc
    src/base/BasicController.cpp
    src/base/NetworkUtils.cpp
    src/MainServiceController.cpp
)

# Add the library
# ---------------
if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME_L} OBJECT ${libsrc})
    add_library(${PROJECT_NAME_L} SHARED $<TARGET_OBJECTS:objlib>)
else()
    add_library(${PROJECT_NAME_L} STATIC ${libsrc})
endif()

# Create an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME_L} ALIAS ${PROJECT_NAME_L})

# Include project directories in target
# -------------------------------------
target_include_directories(${PROJECT_NAME_L}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_target_compiler_flags(${PROJECT_NAME_L})

# Include external libs
# ---------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/boost-cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/openssl-cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/cpprestsdk)

target_link_libraries(${PROJECT_NAME_L}
    PUBLIC
        Boost::system
        Boost::thread
        Boost::log
        Boost::program_options
        Boost::chrono

        ssl
        crypto

        cpprest
)

message(STATUS "Setting target properties - done")

# -----------------------------------------------------------------------------
# Installation instructions
# -----------------------------------------------------------------------------
# Used to implement 'make install' and packaging
# Installing makes a package generally available to the users of the system by
#   installing its components into a well-known prefix (e.g. /usr, /usr/local)
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Create a a version file for the project
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create a config file for the project
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install the ProjectConfig.cmake and ProjectConfigVersion.cmake
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Add the library to the "export-set"
install(
    TARGETS
        ${PROJECT_NAME_L}
    EXPORT
        ${PROJECT_NAME_L}-targets
    LIBRARY DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

set_target_properties(${PROJECT_NAME_L} PROPERTIES EXPORT_NAME ${PROJECT_NAME})

install(
    DIRECTORY
        include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export the targets to a script
install(
    EXPORT  # Generate target export files for install trees
        ${PROJECT_NAME_L}-targets
    FILE
        ${PROJECT_NAME}Targets.cmake
    NAMESPACE
        ${PROJECT_NAME}::  # ${PROJECT_NAME}::${PROJECT_NAME_L}
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# -----------------------------------------------------------------------------
# Export from the build tree
# -----------------------------------------------------------------------------
# Allows use of find_package without the use of a find module

# Create a build-directory exported targets file
export(
    EXPORT
        ${PROJECT_NAME_L}-targets
    FILE
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
    NAMESPACE
        ${PROJECT_NAME}
)

# Register package
export(PACKAGE ${PROJECT_NAME})

# -----------------------------------------------------------------------------
# Testing, samples, and code coverage
# -----------------------------------------------------------------------------
if(BUILD_TESTING)  # Handles code coverage
    add_subdirectory(tests)
endif()

if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()
