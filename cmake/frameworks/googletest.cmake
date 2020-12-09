##
#
# \file googletest.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  A CMake script to fetch googletest (gtest, gmock) at
#         configure time and also adds it to the main build.
#         However, in case googletest is already present on the
#         system, it will be used instead.
#
# \see    https://cmake.org/cmake/help/latest/module/FetchContent.html
#
##

#################################################################
#                          Variables                            #
#################################################################

set(GTEST_VERSION 1.10.0
    CACHE STRING "Which release are you interested in?"
    FORCE)

#################################################################
#                           Install                             #
#################################################################

# Find installed googletest package
find_package(GTest ${GTEST_VERSION} EXACT QUIET)

if(GTest_FOUND)

    #---------------------------------------------------------------#
    #                     Search directories                        #
    #---------------------------------------------------------------#

    # Add googletest headers to include directories
    include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

    # Add directory containing googletest/googlemock libraries
    # to the linker's search path. pthread is required by gtest
    link_libraries(${GTEST_LIBRARIES};pthread)

else()

    #---------------------------------------------------------------#
    #                            Fetch                              #
    #---------------------------------------------------------------#

    # Gtest and Gmock are built as static libraries so installing
    # them is useless. We just need to link with those libraries (*.a
    # files when compiling unit tests
    #
    # See build/_deps/googletest-src/CMakeLists.txt
    set(INSTALL_GTEST OFF
        CACHE BOOL "Disable installation of googletest")

    include(FetchContent)
    FetchContent_Declare(
	    googletest
	    GIT_REPOSITORY https://github.com/google/googletest.git
	    GIT_TAG        release-${GTEST_VERSION}
    )

    # After the following call, the CMake targets defined by googletest
    # will be defined and available to the rest of the build
    FetchContent_MakeAvailable(googletest)

    #---------------------------------------------------------------#
    #                     Search directories                        #
    #---------------------------------------------------------------#

    # Add googletest headers to include directories
    include_directories(SYSTEM ${googletest_SOURCE_DIR}/googletest/include)

    # Add googlemock headers to include directories
    include_directories(SYSTEM ${googlemock_SOURCE_DIR}/googlemock/include)

    # Add directory containing googletest/googlemock static libraries
    # to the linker's search path
    link_directories(SYSTEM ${CMAKE_BINARY_DIR}/lib)

endif()
