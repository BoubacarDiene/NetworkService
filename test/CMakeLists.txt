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

# From https://cmake.org/cmake/help/latest/command/install.html:
#   When TYPE is specified, a destination will then be set
#   automatically by taking the corresponding variable from
#   GNUInstallDirs, or by using a built-in default if that variable
#   is not defined

# Copy the generated dependency graph to share/ directory when
# "make install" is called
include(GNUInstallDirs)
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
message(STATUS "Preparing googletest...")
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
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockConfig.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockExecutor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockExecutor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockLogger.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockLogger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockNetwork.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockNetwork.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockOsal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockOsal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockReader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockRule.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockRule.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockRuleFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockRuleFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockWriter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks/MockWriter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/config/FakeConfigTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/config/JsonConfigTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/firewall/RuleFactoryTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/firewall/RuleTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/fakes/MockOS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/fakes/MockOS.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/fakes/OS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/InterfaceTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/LayerTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/network/NetworkTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/service/NetworkServiceTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/osal/fakes/MockOS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/osal/fakes/MockOS.h
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/osal/fakes/OS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/command/osal/LinuxTest.cpp
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
add_subdirectory(plugins)
