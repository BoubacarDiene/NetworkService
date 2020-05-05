##
#
# \file pre-commit-hook.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMake script to copy pre-commit-hook.in template to git
#         hooks directory as pre-commit bash script and replace
#         CMake's variable inside with their value
#
##

#################################################################
#                          Installation                         #
#################################################################

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/.git/hooks)
    message(WARNING "Not a valid git project")
else()
    if (EXISTS ${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit)
        message(VERBOSE "pre-commit script already installed")
    else()
        configure_file(
            ${CMAKE_SOURCE_DIR}/cmake/git/pre-commit-hook.in
            ${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit @ONLY
        )
    endif()
endif()
