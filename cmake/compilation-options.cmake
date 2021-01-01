##
#
# \file compilation-options.cmake
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  A CMake script to configure the compiler by setting the
#         C++ language version and whether it is a development or
#         a release. In debug mode, several tools and flags are
#         enabled to help analysing the source code (linting, static
#         analysis, link what you use, include what you use, ...)
#
# Additional flags can be added depending on CMAKE_BUILD_TYPE (
# Release or Debug):
#
#     -DENABLE_ASAN=ON      Enable address sanitizer
#     -DENABLE_SECURITY=ON  Enable security flags
#     -DENABLE_COVERAGE=ON  Enable code coverage flags
#     -DENABLE_IWYU=ON      Enable Include What You Use
#     -DENABLE_LWYU=ON      Enable Link What You Use
#
# If CMAKE_BUILD_TYPE is not explicitly set to Debug, the project
# is built in Release mode. In Debug mode, ASAN, SECURITY and LWYU
# are automatically enabled.
#
##

#################################################################
#                          Options                              #
#################################################################

# Allow to enable/disable ASAN in Release build
#
# Note:
# In Debug build, ASAN is enabled automatically
option(ENABLE_ASAN "Enable Address sanitizer" OFF)

# Allow to add/remove security flags in Release build
#
# Note:
# In Debug build, security flags are enabled automatically
option(ENABLE_SECURITY "Add security flags" OFF)

# Allow to add/remove gcov's related flags
# This option will be almost used in test mode
option(ENABLE_COVERAGE "Add necessary flags to use gcov" OFF)

# Allow to enable/disable the IWYU tool
#
# Note:
# OFF by default because this tool is a bit verbose due to the
# fact that it expects for each source file to explicitly include
# all header files it uses. Consider A.h which includes B.h, if
# Main.cpp includes A.h but also uses functions in B.h, IWYU will
# warn because a #include "B.h" is not found in Main.cpp
option(ENABLE_IWYU "Enable Include What You Use" OFF)

# Allow to enable/disable the LWYU tool in Release build
#
# Note:
# It could be ON by default because it's really useful to make
# sure more than the needed libraries are not linked to. However,
# it will be automatically enabled in Debug build
option(ENABLE_LWYU "Enable Link What You Use" OFF)

#################################################################
#                      Compile commands                         #
#################################################################

# Set "CMAKE_EXPORT_COMPILE_COMMANDS" to "ON" to ask CMake provide
# compile_commands.json file to tools like clang-tidy (which can't
# find system headers if not provided)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#################################################################
#                           Language                            #
#################################################################

# -std=c++<version> instead of -std=gnu++<version>
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#################################################################
#                      Compilation options                      #
#################################################################

# Common flags
# See + https://linux.die.net/man/1/gcc
#     + https://security.stackexchange.com/questions/24444/what-
#       is-the-most-hardened-set-of-options-for-gcc-compiling-c-c
list(APPEND LDFLAGS_OPTIONS "")
list(APPEND CFLAGS_OPTIONS -Wall -Wextra -Werror
                           -Wconversion -Wsign-conversion
                           -Wparentheses -Winit-self -Wredundant-decls
                           -Wcast-qual -Wcast-align -Wshadow)

# Force build type to Release if not defined
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release" FORCE)
endif()

# Settings depending on build type
if (CMAKE_BUILD_TYPE MATCHES "^Debug$")
    message(STATUS "Debug build")
    list(APPEND CFLAGS_OPTIONS -g)

    set(ENABLE_ASAN ON)
    set(ENABLE_SECURITY ON)
    set(ENABLE_LWYU ON)
    set(ENABLE_COVERAGE ON)
else()
    message(STATUS "Release build")
    list(APPEND CFLAGS_OPTIONS -DNDEBUG)
endif()

# Address sanitizer
if (ENABLE_ASAN)
    message(STATUS "Add address sanitizer flags")
    list(APPEND LDFLAGS_OPTIONS -fsanitize=address -fno-omit-frame-pointer)
    list(APPEND CFLAGS_OPTIONS -fsanitize=address -fno-omit-frame-pointer)
endif()

# Security
if (ENABLE_SECURITY)
    message(STATUS "Add security flags")
    list(APPEND LDFLAGS_OPTIONS -Wl,-z,now -Wl,-z,relro -Wl,-z,noexecstack)
    list(APPEND CFLAGS_OPTIONS -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security
                               -fstack-protector-all -Wstack-protector --param ssp-buffer-size=4
                               -pie -fPIE -ftrapv)
endif()

# Add logic to generate output files that can be processed by the gcov command.
#
# Notes:
# Optimization is disabled (-O0) because it may combine lines of code and
# otherwise change the flow of execution in the program.
# With optimization enabled, the compiler can decide to inline a function,
# etc.
#
# See
# - https://gcovr.com/en/stable/guide.html
# - https://gcc.gnu.org/onlinedocs/gcc/Gcov.html#Gcov
if (ENABLE_COVERAGE)
    message(STATUS "Add coverage flags")
    list(APPEND CFLAGS_OPTIONS --coverage -O0)
    list(APPEND LDFLAGS_OPTIONS --coverage)
endif()

# Set "CMAKE_LINK_WHAT_YOU_USE" to "TRUE" to ask CMake add the
# linker flag "-Wl,--no-as-needed" and run the command "ldd -r -u"
# on the target after it is linked.
#
# Notes:
# - This is only applicable to executable and shared library targets
#   and will only work when ld and ldd accept the flags used
# - See https://linux.die.net/man/1/ld
if (ENABLE_LWYU)
    message(STATUS "Enable Link What You Use")
    set(CMAKE_LINK_WHAT_YOU_USE TRUE)
endif()

# Enable "Include What You Use" to make sure to always include the
# exact list of required headers
#
# Note:
# - "--no_fwd_decls": Do not use forward declarations even if it can speed up
#                     compilation
# - For the pros and cons of using forward declarations, see:
#   https://google.github.io/styleguide/cppguide.html#Forward_Declarations
if (ENABLE_IWYU)
    find_program(IWYU_EXECUTABLE NAMES iwyu)
    if (IWYU_EXECUTABLE)
        message(STATUS "Enable Include What You Use")
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_EXECUTABLE}
            -Xiwyu --no_fwd_decls -Xiwyu --cxx17ns)
    endif()
endif()

# Adds options to the COMPILE_OPTIONS directory property.
# These options are used when compiling targets from the current
# directory and below. COMPILE_OPTIONS is the list of options to
# pass to the compiler
add_compile_options(${CFLAGS_OPTIONS})

# Add options to the link step for executable, shared library or
# module library targets in the current directory and below that
# are added after this command is invoked
add_link_options(${LDFLAGS_OPTIONS})
