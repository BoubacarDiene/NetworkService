##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to build the config plugin
#
##
#################################################################
#                      Object libraries                         #
#################################################################

# Object libraries are not handled the same way as for other libs
# because when defined closer to the related component (mock,
# json, ...), referencing the objects here fails.
#
# Example: For $<TARGET_OBJECTS:${TARGET_CONFIG_MOCK}>, instead
#          of $<TARGET_OBJECTS:xxx-config-mock>, the following
#          error is returned:
#
#     $<TARGET_OBJECTS:>
#     Objects of target "" referenced but no such target exists.
#
# Note:
#   The empty quotes are necessary because add_library() requires
#   a list of sources files which I add in subdirectories using
#   target_sources

# Mock
set(TARGET_CONFIG_MOCK ${CMAKE_PROJECT_NAME}-config-mock
    CACHE INTERNAL "Name of target to build config/mock" FORCE)
add_library(${TARGET_CONFIG_MOCK} OBJECT "")

# Json
set(TARGET_CONFIG_JSON ${CMAKE_PROJECT_NAME}-config-json
    CACHE INTERNAL "Name of target to build config/json" FORCE)
add_library(${TARGET_CONFIG_JSON} OBJECT "")

#################################################################
#                            Target                             #
#################################################################

# Make target name globally available for dependencies
set(TARGET_PLUGINS_CONFIG ${CMAKE_PROJECT_NAME}-plugins-config
    CACHE STRING "Name of target to build the config plugin"
    FORCE)

# Build the config plugin as a static library
add_library(${TARGET_PLUGINS_CONFIG}
    STATIC
        $<TARGET_OBJECTS:${TARGET_CONFIG_MOCK}>
        $<TARGET_OBJECTS:${TARGET_CONFIG_JSON}>)

#################################################################
#                       Subdirectories                          #
#################################################################

# Get list of directories inside src/ directory
list_subdirectories(subdirectories ${CMAKE_CURRENT_SOURCE_DIR})

# Add all subdirectories that contain a CMakeLists.txt file
foreach(subdirectory ${subdirectories})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt)
        message(STATUS "Add config directory: ${subdirectory}")
        add_subdirectory(${subdirectory})
    endif()
endforeach()

#################################################################
#                          Sources                              #
#################################################################

target_sources(${TARGET_PLUGINS_CONFIG}
    PRIVATE
        Config.cpp
    PUBLIC
        Config.h
)
