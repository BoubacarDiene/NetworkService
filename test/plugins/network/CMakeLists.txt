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

set(LAYER_TEST_EXECUTABLE_NAME LayerTest)
set(INTERFACE_TEST_EXECUTABLE_NAME InterfaceTest)
set(NETWORK_TEST_EXECUTABLE_NAME NetworkTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add layer executable to the project
add_executable(${LAYER_TEST_EXECUTABLE_NAME}
    LayerTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/network/layer/Setup.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockWriter.cpp)

target_link_libraries(${LAYER_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${LAYER_TEST_EXECUTABLE_NAME}
    ${LAYER_TEST_EXECUTABLE_NAME})

# Add interface executable to the project
add_executable(${INTERFACE_TEST_EXECUTABLE_NAME}
    InterfaceTest.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/network/interface/Setup.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/parser/Parser.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockExecutor.cpp)

target_link_libraries(${INTERFACE_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${INTERFACE_TEST_EXECUTABLE_NAME}
    ${INTERFACE_TEST_EXECUTABLE_NAME})

# Add network executable to the project
add_executable(${NETWORK_TEST_EXECUTABLE_NAME}
    NetworkTest.cpp
    fakes/Wrapper.cpp
    fakes/MockWrapper.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/network/Network.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/network/interface/Setup.cpp
    ${CMAKE_SOURCE_DIR}/src/plugins/network/layer/Setup.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/parser/Parser.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/helper/Errno.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockWriter.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockExecutor.cpp)

target_link_libraries(${NETWORK_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

target_include_directories(${NETWORK_TEST_EXECUTABLE_NAME}
    SYSTEM BEFORE PUBLIC fakes)

add_test(${NETWORK_TEST_EXECUTABLE_NAME}
    ${NETWORK_TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS
            ${LAYER_TEST_EXECUTABLE_NAME}
            ${INTERFACE_TEST_EXECUTABLE_NAME}
            ${NETWORK_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
