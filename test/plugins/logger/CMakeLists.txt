##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
#         plugins/network directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(TEST_EXECUTABLE_NAME StdLoggerTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add stdLogger executable to the project
add_executable(${TEST_EXECUTABLE_NAME}
    StdLoggerTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/logger/StdLogger.cpp)

target_link_libraries(${TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${TEST_EXECUTABLE_NAME}
    ${TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
