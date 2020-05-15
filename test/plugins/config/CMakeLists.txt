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

#################################################################
#                     Build and add test                        #
#################################################################

# Add jsonConfig executable to the project
add_executable(${JSON_CONFIG_TEST_EXECUTABLE_NAME}
    JsonConfigTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/config/JsonConfig.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockReader.cpp)

target_link_libraries(${JSON_CONFIG_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${JSON_CONFIG_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
