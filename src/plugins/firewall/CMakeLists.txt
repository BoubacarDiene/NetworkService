##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to build the firewall plugin
#
##

#################################################################
#                            Target                             #
#################################################################

# Make target name globally available for dependencies
set(TARGET_PLUGINS_FIREWALL ${CMAKE_PROJECT_NAME}-plugins-firewall
    CACHE STRING "Name of target to build the firewall plugin"
    FORCE)

# Build the firewall plugin as a static library
add_library(${TARGET_PLUGINS_FIREWALL}
    STATIC
        $<TARGET_OBJECTS:${TARGET_UTILS_COMMAND}>
        $<TARGET_OBJECTS:${TARGET_UTILS_HELPER}>)

#################################################################
#                          Sources                              #
#################################################################

target_sources(${TARGET_PLUGINS_FIREWALL}
    PRIVATE
        Rule.cpp
        RuleFactory.cpp
    PUBLIC
        RuleFactory.h
)
