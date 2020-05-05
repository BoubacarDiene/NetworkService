##
#
# \file clang-format.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMake script to use Clang's code formatter based on
#         .clang-format config file. It adds a new build target:
#
#         - "make clang-format"
#
# IMPORTANT: Before including this script, make sure the variable
#            ALL_CXX_SOURCE_FILES is set. As the name suggests, it
#            contains the complete list of source files (*.cpp,
#            *.hpp, *.h)
#
# IMPORTANT: Before including this script, make sure the variable
#            ALL_CXX_SOURCE_FILES is set. As the name suggests, it
#            contains the full list of source files
#
##

#################################################################
#                        Dependencies                           #
#################################################################

# Make sure clang-format is installed
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)

#################################################################
#                          Targets                              #
#################################################################

# Define "clang-format" target
# "make clang-format" has to be used to format the source code
# Note:
#   Stage your source files first (git add -A) if you need to see
#   the changes
if (CLANG_FORMAT_EXECUTABLE AND EXISTS ${CMAKE_SOURCE_DIR}/.clang-format)
    add_custom_target(clang-format
        COMMENT "Starting clang-format..."
        COMMAND ${CLANG_FORMAT_EXECUTABLE}
            -i
            -style=file
            -fallback-style=none
            ${ALL_CXX_SOURCE_FILES}
    )
endif()
