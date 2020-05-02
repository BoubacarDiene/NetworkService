##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to build command, file and helper classes
#
##

#################################################################
#                       Subdirectories                          #
#################################################################

# Get list of directories inside src/ directory
list_subdirectories(subdirectories ${CMAKE_CURRENT_SOURCE_DIR})

# Add all subdirectories that contain a CMakeLists.txt file
foreach(subdirectory ${subdirectories})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt)
        message(STATUS "Add utils directory: ${subdirectory}")
        add_subdirectory(${subdirectory})
    endif()
endforeach()
