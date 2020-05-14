##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
#         service directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(TEST_EXECUTABLE_NAME NetworkServiceTest)

#################################################################
#                     Build and add test                        #
#################################################################

add_executable(${TEST_EXECUTABLE_NAME}
    NetworkServiceTest.cpp
    ${CMAKE_SOURCE_DIR}/src/service/NetworkService.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockConfig.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockNetwork.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockOsal.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockRule.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockRuleFactory.cpp)

target_link_libraries(${TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${TEST_EXECUTABLE_NAME}
    ${TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
