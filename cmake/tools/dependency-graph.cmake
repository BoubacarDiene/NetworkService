##
#
# \file dependency-graph.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to generate a dependency graph showing
#         how the different components of this service are linked
#         together
#
#         This script add a new build target:
#         - "make dependency-graph"
#
##

#################################################################
#                        Dependencies                           #
#################################################################

# Make sure Graphviz dot utility is installed
find_package(Doxygen REQUIRED COMPONENTS dot)

#################################################################
#                         Variables                             #
#################################################################

# Set the working directory and make sure it exists
set(GRAPHVIZ_WORKING_DIR ${CMAKE_BINARY_DIR}/dependency-graph)
if(NOT EXISTS ${GRAPHVIZ_WORKING_DIR})
    file(MAKE_DIRECTORY ${GRAPHVIZ_WORKING_DIR})
endif()

# Set output files name
set(GRAPHVIZ_DOT dependency_graph.dot)
set(GRAPHVIZ_PNG dependency_graph.png)

#################################################################
#                          Targets                              #
#################################################################

# Define "dependency-graph" target
# "make dependency-graph" has to be used to generate the .png file
add_custom_target(dependency-graph
    COMMAND ${CMAKE_COMMAND} -E echo_append "Generating dependency graph..."
    COMMAND ${CMAKE_COMMAND} "--graphviz=${GRAPHVIZ_DOT}" .. > /dev/null 2>&1
    COMMAND ${DOXYGEN_DOT_EXECUTABLE} -Tpng ${GRAPHVIZ_DOT}
                                      -o ${GRAPHVIZ_PNG} > /dev/null 2>&1
    COMMAND ${CMAKE_COMMAND} -E echo "Done"
    WORKING_DIRECTORY ${GRAPHVIZ_WORKING_DIR}
)

#################################################################
#                        Installation                           #
#################################################################

# From https://cmake.org/cmake/help/latest/command/install.html:
#   When TYPE is specified, a destination will then be set
#   automatically by taking the corresponding variable from
#   GNUInstallDirs, or by using a built-in default if that variable
#   is not defined

# Copy the generated dependency graph to share/ directory when
# "make install" is called
include(GNUInstallDirs)
install(FILES ${GRAPHVIZ_WORKING_DIR}/${GRAPHVIZ_PNG}
        DESTINATION ${CMAKE_INSTALL_DATADIR}/dependency-graph
        OPTIONAL)
