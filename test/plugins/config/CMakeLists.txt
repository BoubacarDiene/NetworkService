##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
#         plugins/config directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(JSON_CONFIG_TEST_EXECUTABLE_NAME JsonConfigTest)
set(FAKE_CONFIG_TEST_EXECUTABLE_NAME FakeConfigTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add jsonConfig executable to the project
add_executable(${JSON_CONFIG_TEST_EXECUTABLE_NAME}
    JsonConfigTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/config/JsonConfig.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockReader.cpp)

target_link_libraries(${JSON_CONFIG_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${JSON_CONFIG_TEST_EXECUTABLE_NAME}
    ${JSON_CONFIG_TEST_EXECUTABLE_NAME})

# Add fakeConfig executable to the project
add_executable(${FAKE_CONFIG_TEST_EXECUTABLE_NAME}
    FakeConfigTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/config/FakeConfig.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockReader.cpp)

target_link_libraries(${FAKE_CONFIG_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${FAKE_CONFIG_TEST_EXECUTABLE_NAME}
    ${FAKE_CONFIG_TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS
            ${JSON_CONFIG_TEST_EXECUTABLE_NAME}
            ${FAKE_CONFIG_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
