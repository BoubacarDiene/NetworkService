##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to generate and install documentation
#
# \note   Doxyfile.in file has been generated using command:
#         $ doxygen -g doc/Doxyfile.in
#
##

#################################################################
#                        Dependencies                           #
#################################################################

# Make sure doxygen is installed
find_package(Doxygen)

# Replace cmake's variables in Doxyfile.in
configure_file(Doxyfile.in Doxyfile)

#################################################################
#                         Variables                             #
#################################################################

set(DOXYGEN_INPUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#################################################################
#                          Targets                              #
#################################################################

# Define "doc" target
# "make doc" has to be used to generate documentation
add_custom_target(doc
    COMMENT "Building API Documentation..."
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT} > /dev/null 2>&1
)

#################################################################
#                        Installation                           #
#################################################################

# From https://cmake.org/cmake/help/latest/command/install.html:
#   When TYPE is specified, a destination will then be set
#   automatically by taking the corresponding variable from
#   GNUInstallDirs, or by using a built-in default if that variable
#   is not defined

# Copy documentation to output directory when "make install" is
# called
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
        TYPE DOC
        OPTIONAL)
