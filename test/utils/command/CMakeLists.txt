##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit test(s) for classes in
#         utils/command directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(PARSER_TEST_EXECUTABLE_NAME ParserTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add test executable to the project
add_executable(${PARSER_TEST_EXECUTABLE_NAME}
    ParserTest.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/Parser.cpp)

# Link with required frameworks
target_link_libraries(${PARSER_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

# Add the test to the project to be run by ctest
add_test(${PARSER_TEST_EXECUTABLE_NAME}
    ${PARSER_TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${PARSER_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
