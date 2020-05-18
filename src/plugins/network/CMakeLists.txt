##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to build the network plugin
#
##

#################################################################
#                            Target                             #
#################################################################

# Make target name globally available for dependencies
set(TARGET_PLUGINS_NETWORK ${CMAKE_PROJECT_NAME}-plugins-network
    CACHE STRING "Name of target to build the network plugin"
    FORCE)

# Build the network plugin as a static library
add_library(${TARGET_PLUGINS_NETWORK}
    STATIC
        $<TARGET_OBJECTS:${TARGET_UTILS_COMMAND}>
        $<TARGET_OBJECTS:${TARGET_UTILS_FILE_WRITER}>
        $<TARGET_OBJECTS:${TARGET_UTILS_HELPER}>)

#################################################################
#                          Sources                              #
#################################################################

target_sources(${TARGET_PLUGINS_NETWORK}
    PRIVATE
        Network.cpp
        Wrapper.cpp
        interface/Setup.cpp
        layer/Setup.cpp
    PUBLIC
        Network.h
)
