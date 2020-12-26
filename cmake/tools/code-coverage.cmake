##
#
# \file clang-tidy.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   May 2020
#
# \brief  CMake script to use gcovr: a utility for managing the
#         use of the GNU gcov utility and generating summarized
#         code coverage results. It adds the following new build:
#
#         - "make coverage"
#
# \note
# 1- Coverage flags are supposed to be set (ENABLE_COVERAGE=ON)
#    ENABLE_COVERAGE is automatically set to ON in Debug mode
#
# 2- ENABLE_UNIT_TESTING=ON is expected
#
# 3- The source are supposed to be found in src/ directory. That
#    can be changed using the following command:
#
#   set(COVERAGE_ROOT_DIR <path_to_source_files>
#    CACHE PATH "Path to directory containing source files" FORCE)
#
# \usage
#   cmake .. -DCMAKE_INSTALL_PREFIX=./out -DENABLE_UNIT_TESTING=ON
#   make && ctest
#
#   make coverage && make install
#
#   index.html: out/share/coverage/html/index.html
#   cobertura.xml: out/share/coverage/html/cobertura.xml
#

###################################################################
#                          Variables                            #
#################################################################

# Which directory to use as --root?
set(COVERAGE_ROOT_DIR ${CMAKE_SOURCE_DIR}/src
    CACHE PATH "Path to directory containing source files")

# Name of a directory to exclude. It is relative to root directory
# provided above. This variable can be used to exclude a directory
# that you don't need to be part of the report.
# In case the specified directory does not exist, there will be no
# effect.
set(COVERAGE_EXCLUDE_DIR none
    CACHE PATH "Name of directory to exclude from report")

#################################################################
#                        Dependencies                           #
#################################################################

# Make sure coverage tools are installed
find_program(GCOV_EXECUTABLE NAMES gcov)
find_program(GCOVR_EXECUTABLE NAMES gcovr)
find_program(GENHTML_EXECUTABLE NAMES genhtml)

#################################################################
#                          Targets                              #
#################################################################

if (ENABLE_UNIT_TESTING
    AND GCOV_EXECUTABLE AND GCOVR_EXECUTABLE AND GENHTML_EXECUTABLE)
    # Create working directories if they do not exist
    set(GCOVR_WORKING_DIR ${CMAKE_BINARY_DIR}/coverage)
    if (NOT EXISTS ${GCOVR_WORKING_DIR})
        file(MAKE_DIRECTORY ${GCOVR_WORKING_DIR})
    endif()

    set(GCOVR_WORKING_DIR_FOR_HTML_REPORT ${GCOVR_WORKING_DIR}/html)
    if (NOT EXISTS ${GCOVR_WORKING_DIR_FOR_HTML_REPORT})
        file(MAKE_DIRECTORY ${GCOVR_WORKING_DIR_FOR_HTML_REPORT})
    endif()

    set(GCOVR_WORKING_DIR_FOR_XML_REPORT ${GCOVR_WORKING_DIR}/xml)
    if (NOT EXISTS ${GCOVR_WORKING_DIR_FOR_XML_REPORT})
        file(MAKE_DIRECTORY ${GCOVR_WORKING_DIR_FOR_XML_REPORT})
    endif()

    # Add coverage targets
    # See https://gcovr.com/en/stable/guide.html
    #     https://gcc.gnu.org/onlinedocs/gcc/Gcov-Intro.html#Gcov-Intro
    add_custom_target(coverage-html
        COMMENT "Generating html report..."
        COMMAND ${GCOVR_EXECUTABLE}
            -r ${COVERAGE_ROOT_DIR} ${CMAKE_BINARY_DIR}
            -e ".*${COVERAGE_EXCLUDE_DIR}.*"
            --branches --html --html-details
            -o index.html
        WORKING_DIRECTORY ${GCOVR_WORKING_DIR_FOR_HTML_REPORT}
    )

    add_custom_target(coverage-xml
        COMMENT "Generating xml report..."
        COMMAND ${GCOVR_EXECUTABLE}
            -r ${COVERAGE_ROOT_DIR} ${CMAKE_BINARY_DIR}
            -e ".*${COVERAGE_EXCLUDE_DIR}.*"
            --branches --xml-pretty
            -o cobertura.xml
        WORKING_DIRECTORY ${GCOVR_WORKING_DIR_FOR_XML_REPORT}
    )

    add_custom_target(coverage)
    foreach (target coverage-html coverage-xml)
        add_dependencies(coverage ${target})
    endforeach()

    # Add command to install reports
    #
    # From https://cmake.org/cmake/help/latest/command/install.html:
    #   When TYPE is specified, a destination will then be set
    #   automatically by taking the corresponding variable from
    #   GNUInstallDirs, or by using a built-in default if that variable
    #   is not defined

    # Copy report to output directory when "make install" is called
    install(DIRECTORY ${GCOVR_WORKING_DIR}
            TYPE DATA
            OPTIONAL)
endif()
