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
#                           Target                              #
#################################################################

# Make target name globally available for dependencies
set(TARGET_PLUGINS_CONFIG ${CMAKE_PROJECT_NAME}-plugins-config
    CACHE STRING "Name of target to build the config plugin"
    FORCE)

# Build the config plugin as a static library
add_library(${TARGET_PLUGINS_CONFIG} STATIC "")

#################################################################
#                    Conditional compilation                    #
#################################################################

if (CONFIG_LOADER MATCHES mock)
    target_sources(${TARGET_PLUGINS_CONFIG}
        PRIVATE MockConfig.cpp PUBLIC Config.h)
else()
    target_sources(${TARGET_PLUGINS_CONFIG}
        PRIVATE JsonConfig.cpp PUBLIC Config.h)
endif()
