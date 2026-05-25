cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME BGLittleFSLib)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

#message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

add_library(${CMAKE_PROJECT_NAME}
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGSFSDirectory.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGSFSFilename.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGSFSGetPathVisitor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGSFSNode.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGSFSNodeVisitor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGSFSTreeVisitor.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/AGS_LittleFS.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/..
) 


