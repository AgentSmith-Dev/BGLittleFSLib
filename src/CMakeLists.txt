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