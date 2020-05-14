##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to prepare googletest and googlemock;
#         and add subdirectories containing unit tests
#
##

#################################################################
#                           Variables                           #
#################################################################

set(TESTS_INSTALL_DIR ${CMAKE_INSTALL_BINDIR}/tests)

#################################################################
#                          Frameworks                           #
#################################################################

# Add script to make googletest and googlemock available
#
# FIXME: Gmock can't compile with flags used in this project:
#     error: conversion to 'long unsigned int' from 'int' may
#     change the sign of the result [-Werror=sign-conversion]
#
# Add "-Wno-error=sign-conversion" to make the build pass.
set(CMAKE_CXX_FLAGS -Wno-error=sign-conversion)
include(${CMAKE_SOURCE_DIR}/cmake/frameworks/googletest.cmake)

#################################################################
#                          Test files                           #
#################################################################

# Make test files list globally available for clang-format and
# clang-tidy tools. Note that test files are explicitly listed
# here because "If no CMakeLists.txt file changes when a source
# is added or removed then the generated build system cannot know
# when to ask CMake to regenerate"
set(ALL_CXX_TEST_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockConfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockLogger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockNetwork.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockOsal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockRule.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockRuleFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/service/NetworkServiceTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/ExecutorTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/ParserTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/ReaderTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/file/WriterTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/helper/ErrnoTest.cpp
    CACHE INTERNAL "All *.cpp, *.h and *.hpp files of the project"
    FORCE)

#################################################################
#                       Search directories                      #
#################################################################

include_directories(.)

#################################################################
#                       Subdirectories                          #
#################################################################

add_subdirectory(utils)
add_subdirectory(service)
