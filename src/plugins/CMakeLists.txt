##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add all plugins into build list
#
##

#################################################################
#                       Subdirectories                          #
#################################################################

# Get list of directories inside plugins/ directory
list_subdirectories(subdirectories ${CMAKE_CURRENT_SOURCE_DIR})

# Add all subdirectories that contain a CMakeLists.txt file
foreach (subdirectory ${subdirectories})
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdirectory}/CMakeLists.txt)
        message(STATUS "Add plugin directory: ${subdirectory}")
        add_subdirectory(${subdirectory})
    endif()
endforeach()
