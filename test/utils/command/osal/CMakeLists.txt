##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
#         utils/command/osal directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(TEST_EXECUTABLE_NAME LinuxTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add Linux executable to the project
add_executable(${TEST_EXECUTABLE_NAME}
    LinuxTest.cpp
    fakes/MockWrapper.cpp
    fakes/Wrapper.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/executor/osal/Linux.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/helper/Errno.cpp
    ${CMAKE_SOURCE_DIR}/test/mocks/MockLogger.cpp)

target_link_libraries(${TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${TEST_EXECUTABLE_NAME}
    ${TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
