##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
#         plugins/firewall directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(RULE_TEST_EXECUTABLE_NAME RuleTest)
set(RULE_FACTORY_TEST_EXECUTABLE_NAME RuleFactoryTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add rule executable to the project
add_executable(${RULE_TEST_EXECUTABLE_NAME}
    RuleTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/firewall/Rule.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/parser/Parser.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockExecutor.cpp)

target_link_libraries(${RULE_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${RULE_TEST_EXECUTABLE_NAME}
    ${RULE_TEST_EXECUTABLE_NAME})

# Add rule factory executable to the project
add_executable(${RULE_FACTORY_TEST_EXECUTABLE_NAME}
    RuleFactoryTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/firewall/RuleFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/firewall/Rule.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/parser/Parser.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockExecutor.cpp)

target_link_libraries(${RULE_FACTORY_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${RULE_FACTORY_TEST_EXECUTABLE_NAME}
    ${RULE_FACTORY_TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS
            ${RULE_TEST_EXECUTABLE_NAME}
            ${RULE_FACTORY_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
