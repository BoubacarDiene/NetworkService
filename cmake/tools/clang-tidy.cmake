##
#
# \file clang-tidy.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMake script to use clang-tidy: a tool for static C/C++
#         code analysis and linting. This script expects the config
#         file ".clang-tidy", and adds a new build target:
#
#         - "make clang-tidy"
#
# IMPORTANT: Before including this script, make sure the variable
#            ALL_CXX_SOURCE_FILES is set. As the name suggests, it
#            contains the complete list of source files (*.cpp,
#            *.hpp, *.h). Also, ALL_CXX_TEST_FILES has to be set
#            in case unit testing is enabled.
#
##

#################################################################
#                        Dependencies                           #
#################################################################

# Make sure clang-tidy is installed
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)

#################################################################
#                          Targets                              #
#################################################################

# Prepare the complete list of files to take into account
# ALL_CXX_TEST_FILES is empty when unit testing is not enabled
list(APPEND ALL_CXX_SOURCE_FILES ${ALL_CXX_TEST_FILES})

# Define "clang-tidy" target
# "make clang-tidy" has to be used to "lint" the source code
#
# Notes:
# - See https://clang.llvm.org/extra/clang-tidy/
#   and https://clang.llvm.org/extra/clang-tidy/checks/list.html
#       https://github.com/isocpp/CppCoreGuidelines/blob/master/\
#         CppCoreGuidelines.md#Rf-dangle
#
# - set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
#   could be used instead but I prefer having my settings in a
#   .clang-tidy file
if (CLANG_TIDY_EXECUTABLE)
    add_custom_target(clang-tidy
        COMMENT "Starting clang-tidy..."
        COMMAND ${CLANG_TIDY_EXECUTABLE}
            ${ALL_CXX_SOURCE_FILES}
            -p ${CMAKE_BINARY_DIR} > ${CMAKE_BINARY_DIR}/clang_tidy_output.txt
        COMMAND cat ${CMAKE_BINARY_DIR}/clang_tidy_output.txt
    )
endif()
