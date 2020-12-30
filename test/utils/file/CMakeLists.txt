##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMakeLists.txt to build unit tests for classes in
#         utils/file directory
#
##

#################################################################
#                          Variables                            #
#################################################################

set(WRITER_TEST_EXECUTABLE_NAME WriterTest)
set(READER_TEST_EXECUTABLE_NAME ReaderTest)

#################################################################
#                     Build and add test                        #
#################################################################

# Add writer executable to the project
add_executable(${WRITER_TEST_EXECUTABLE_NAME}
    WriterTest.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/file/writer/Writer.cpp)

target_link_libraries(${WRITER_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${WRITER_TEST_EXECUTABLE_NAME}
    ${WRITER_TEST_EXECUTABLE_NAME})

# Add reader executable to the project
add_executable(${READER_TEST_EXECUTABLE_NAME}
    ReaderTest.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/file/reader/Reader.cpp)

target_link_libraries(${READER_TEST_EXECUTABLE_NAME}
    PRIVATE gtest gmock)

add_test(${READER_TEST_EXECUTABLE_NAME}
    ${READER_TEST_EXECUTABLE_NAME})

#################################################################
#                        Installation                           #
#################################################################

install(TARGETS
            ${WRITER_TEST_EXECUTABLE_NAME}
            ${READER_TEST_EXECUTABLE_NAME}
        DESTINATION ${TESTS_INSTALL_DIR})
