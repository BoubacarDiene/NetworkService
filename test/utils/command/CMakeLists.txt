##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
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

# Add parser executable to the project
add_executable(${PARSER_TEST_EXECUTABLE_NAME}
    ParserTest.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/command/parser/Parser.cpp)

target_link_libraries(${PARSER_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${PARSER_TEST_EXECUTABLE_NAME}
    ${PARSER_TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS ${PARSER_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
