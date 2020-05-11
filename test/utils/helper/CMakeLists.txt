##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit test(s) for classes in
#         utils/helper directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(TEST_EXECUTABLE_NAME ErrnoTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add test executable to the project
add_executable(${TEST_EXECUTABLE_NAME}
    ErrnoTest.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/helper/Errno.cpp)

# Link with required frameworks
target_link_libraries(${TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

# Add the test to the project to be run by ctest
add_test(${TEST_EXECUTABLE_NAME} ${TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
