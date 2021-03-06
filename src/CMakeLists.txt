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
set(TARGET_UTILS_FILE_READER ${CMAKE_PROJECT_NAME}-utils-file-reader
    CACHE INTERNAL "Name of target to build utils/file/reader" FORCE)
add_library(${TARGET_UTILS_FILE_READER} OBJECT "")

set(TARGET_UTILS_FILE_WRITER ${CMAKE_PROJECT_NAME}-utils-file-writer
    CACHE INTERNAL "Name of target to build utils/file/writer" FORCE)
add_library(${TARGET_UTILS_FILE_WRITER} OBJECT "")

# Helper
set(TARGET_UTILS_HELPER ${CMAKE_PROJECT_NAME}-utils-helper
    CACHE INTERNAL "Name of target to build utils/helper" FORCE)
add_library(${TARGET_UTILS_HELPER} OBJECT "")

#################################################################
#                          Source files                         #
#################################################################

# Make test files list globally available for clang-format and
# clang-tidy tools. Note that source files are explicitly listed
# here because "If no CMakeLists.txt file changes when a source
# is added or removed then the generated build system cannot know
# when to ask CMake to regenerate"
set(ALL_CXX_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/config/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/config/FakeConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/config/JsonConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/firewall/Rule.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/firewall/Rule.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/firewall/RuleFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/firewall/RuleFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/logger/Logger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/logger/StdLogger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/interface/Interface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/interface/Interface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/layer/Layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/layer/Layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/Network.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/Network.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/plugins/IConfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/plugins/IConfigData.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/plugins/ILogger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/plugins/INetwork.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/plugins/IRule.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/plugins/IRuleFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/NetworkService.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/service/NetworkService.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/executor/Executor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/executor/Executor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/executor/IExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/executor/IOsal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/executor/osal/Linux.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/executor/osal/Linux.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/parser/Parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/parser/Parser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/writer/IWriter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/writer/Writer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/writer/Writer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/reader/IReader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/reader/Reader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/reader/Reader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/helper/Errno.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/helper/Errno.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    CACHE INTERNAL "All *.cpp, *.h and *.hpp files of the project"
    FORCE)

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
