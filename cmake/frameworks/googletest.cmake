##
#
# \file googletest.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  A CMake script to fetch googletest (gtest, gmock) at
#         configure time and also adds it to the main build
#
# \see    https://cmake.org/cmake/help/latest/module/FetchContent.html
#
##

#################################################################
#                          Variables                            #
#################################################################

# Gtest and Gmock are built as static libraries so installing
# them is useless. We just need to link with those libraries (*.a
# files when compiling unit tests
#
# See build/_deps/googletest-src/CMakeLists.txt
set(INSTALL_GTEST OFF
    CACHE BOOL "Disable installation of googletest")

#################################################################
#                            Fetch                              #
#################################################################

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0
)

# After the following call, the CMake targets defined by googletest
# will be defined and available to the rest of the build
FetchContent_MakeAvailable(googletest)

#################################################################
#                     Search directories                        #
#################################################################

# Add googletest headers to include directories
include_directories(SYSTEM ${googletest_SOURCE_DIR}/googletest/include)

# Add googlemock headers to include directories
include_directories(SYSTEM ${googlemock_SOURCE_DIR}/googlemock/include)

# Add directory containing googletest/googlemock static libraries
# to the linker's search path
link_directories(SYSTEM ${CMAKE_BINARY_DIR}/lib)
