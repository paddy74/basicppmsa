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
OPTION(BUILD_SHARED_LIBS "Build shared libraries" OFF)
OPTION(BUILD_TESTS "Build the testing tree" ON)
OPTION(BUILD_SAMPLES "Build the sample application" ON)
OPTION(ENABLE_CODECOV "Enable code coverage reporting" OFF)

# Include additional cmake/ settings
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

include(BuildType)
include(BuildLocation)
include(CompilerFlags)

# -----------------------------------------------------------------------------
# Configure required libraries
# -----------------------------------------------------------------------------
# Boost
find_package(Boost REQUIRED
    COMPONENTS
        system
        thread
        log
        program_options
        chrono
)

# C++ REST SDK
find_package(cpprestsdk REQUIRED)
set(CPPRESTSDK_LIBRARIES "-lboost_system -lcrypto -lssl -lcpprest")

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
target_link_libraries(${PROJECT_NAME_L}
    PRIVATE
        Boost::system
        Boost::thread
        Boost::log
        Boost::program_options
        Boost::chrono

        cpprestsdk::cpprest
)

message(STATUS "Setting target properties - done")

# -----------------------------------------------------------------------------
# Installation instructions
# -----------------------------------------------------------------------------
# Generates installation rules used to implement 'make install' and packaging
# Installing makes a package generally available to the users of the system by
#   installing its components into a well-known prefix (e.g. /usr, /usr/local)
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Create a a version file for the project from the cmake/ configversion file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake  # output
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create a config file for the project from the cmake/ config file
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in  # input
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake  # output
    INSTALL_DESTINATION  # Where the config file will be installed
        ${INSTALL_CONFIGDIR}
)

# Install the <package>Config.cmake and <package>ConfigVersion.cmake files
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Add the library to the "export-set"
# Specifies rules for installing targets from a project
install(
    TARGETS
        ${PROJECT_NAME_L}
    EXPORT  # Associate installed target files with the export
        ${PROJECT_NAME_L}-targets
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set_target_properties(${PROJECT_NAME_L} PROPERTIES EXPORT_NAME ${PROJECT_NAME})

# Installs contents of include/ to the destination directory
install(
    DIRECTORY
        include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generates and installs a CMake file for importing targets from the install
#   tree to other projects
# What is installed by 'make install'
install(
    EXPORT  # Install the export file itself
        ${PROJECT_NAME_L}-targets
    FILE  # Specify name of generated file
        ${PROJECT_NAME}Targets.cmake
    NAMESPACE  # Prepend to the target name
        ${PROJECT_NAME}::  # ${PROJECT_NAME}::${PROJECT_NAME_L}
    DESTINATION  # Where to install
        ${INSTALL_CONFIGDIR}
)

# -----------------------------------------------------------------------------
# Export from the build tree
# -----------------------------------------------------------------------------
# Allows use of find_package without the use of a find module

# Create a file that may be included by outside project to import targets from
#   the current project's build tree
export(
    EXPORT  # Export file generated by install(TARGETS)
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
if(BUILD_TESTS)  # Handles code coverage
    add_subdirectory(tests)
endif()

if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()
