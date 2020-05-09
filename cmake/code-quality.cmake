##
#
# \file code-quality.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMake script to include all other scripts that aims
#         at helping improve the quality of the software. It also
#         defines a custom target to run all code quality-related
#         targets instead of calling them one by one.
#
##

#################################################################
#                        CMake scripts                          #
#################################################################

# Clang: Code formatting
include(${CMAKE_SOURCE_DIR}/cmake/tools/clang-format.cmake)

# Clang: Static analysis and linting
include(${CMAKE_SOURCE_DIR}/cmake/tools/clang-tidy.cmake)

# Graphviz: Dependency graph
include(${CMAKE_SOURCE_DIR}/cmake/tools/dependency-graph.cmake)

# Git hooks
include(${CMAKE_SOURCE_DIR}/cmake/git/pre-commit-hook.cmake)

#################################################################
#                           Target                              #
#################################################################

# To avoid running dependency-graph, clang-format and clang-tidy
# commands one by one
add_custom_target(analysis
    DEPENDS dependency-graph clang-format clang-tidy)
