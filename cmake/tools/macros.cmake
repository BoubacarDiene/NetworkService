##
#
# \file macros.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMake script to define a set of useful macros
#
##

#################################################################
#                        SUBDIRECTORIES                         #
#################################################################

# List all subdirectories inside provided currentDir
macro(list_subdirectories result currentDir)
    file(GLOB children RELATIVE ${currentDir} ${currentDir}/*)
    set(dirList "")
    foreach (child ${children})
        if (IS_DIRECTORY ${currentDir}/${child})
            list(APPEND dirList ${child})
        endif()
    endforeach()
    set(${result} ${dirList})
endmacro()
