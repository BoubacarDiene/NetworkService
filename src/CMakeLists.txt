##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to prepare things necessary to build
#         the source code
#
##

#################################################################
#                      Object libraries                         #
#################################################################

# Object libraries are not handled the same way as for other libs
# because when defined closer to the related component (command,
# file or helper), referencing the objects fails.
#
# Example: For $<TARGET_OBJECTS:${TARGET_UTILS_COMMAND}>, instead
#          of $<TARGET_OBJECTS:xxx-utils-command>, the following
#          error is returned:
#
#     $<TARGET_OBJECTS:>
#     Objects of target "" referenced but no such target exists.
#
# Note:
#   The empty quotes are necessary because add_library() requires
#   a list of sources files which I add in subdirectories using
#   target_sources

# Command
set(TARGET_UTILS_COMMAND ${CMAKE_PROJECT_NAME}-utils-command
    CACHE INTERNAL "Name of target to build utils/command" FORCE)
add_library(${TARGET_UTILS_COMMAND} OBJECT "")

# File
set(TARGET_UTILS_FILE ${CMAKE_PROJECT_NAME}-utils-file
    CACHE INTERNAL "Name of target to build utils/file" FORCE)
add_library(${TARGET_UTILS_FILE} OBJECT "")

# Helper
set(TARGET_UTILS_HELPER ${CMAKE_PROJECT_NAME}-utils-helper
    CACHE INTERNAL "Name of target to build utils/helper" FORCE)
add_library(${TARGET_UTILS_HELPER} OBJECT "")

#################################################################
#                       Subdirectories                          #
#################################################################

add_subdirectory(plugins)
add_subdirectory(service)
add_subdirectory(utils)

#################################################################
#                         Executable                            #
#################################################################

# Link with dependencies and build
add_executable(${EXECUTABLE_NAME} Main.cpp)

target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        ${TARGET_SERVICE}
        ${TARGET_PLUGINS_CONFIG}
        ${TARGET_PLUGINS_FIREWALL}
        ${TARGET_PLUGINS_LOGGER}
        ${TARGET_PLUGINS_NETWORK}
)

# Install to bin directory
install(TARGETS ${EXECUTABLE_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR})
