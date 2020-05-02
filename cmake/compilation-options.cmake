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
# Additional flags can be added depending on BUILD_TYPE environment
# variable (Possible values: debug, asan, secu):
#
# -DBUILD_TYPE="values..."
#     If not set => Release build (default unless "debug" is set)
#     If set,
#         debug => Debug build
#         asan  => Add address sanitizer flags
#         secu  => Add security flags
#
##

#################################################################
#                         CMake's stuffs                        #
#################################################################

# Set "CMAKE_EXPORT_COMPILE_COMMANDS" to "ON" to ask CMake provide
# compile_commands.json file to tools like clang-tidy (which can't
# find system headers if not provided)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#################################################################
#                            Language                           #
#################################################################

# -std=c++<version> instead of -std=gnu++<version>
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#################################################################
#                       Compilation options                     #
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

# Check BUILD_TYPE and define flags accordingly
if(NOT BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    list(APPEND CFLAGS_OPTIONS -s)
else()
    string(REPLACE " " ";" TYPES ${BUILD_TYPE})

    if("debug" IN_LIST TYPES)
        message(STATUS "Debug build")
        set(CMAKE_BUILD_TYPE Debug)

        # Set "CMAKE_LINK_WHAT_YOU_USE" to "TRUE" to ask CMake add the
        # linker flag "-Wl,--no-as-needed" and run the command "ldd -r -u"
        # on the target after it is linked.
        #
        # Notes:
        # - This is only applicable to executable and shared library targets
        #   and will only work when ld and ldd accept the flags used
        # - See https://linux.die.net/man/1/ld
        set(CMAKE_LINK_WHAT_YOU_USE TRUE)

        # Enable "Include What You Use" to make sure to always include the
        # exact list of required headers
        #
        # Note:
        # - "--no_fwd_decls": Do not use forward declarations even if it can speed up
        #                     compilation
        # - For the pros and cons of using forward declarations, see:
        #   https://google.github.io/styleguide/cppguide.html#Forward_Declarations
        find_program(IWYU_EXECUTABLE NAMES iwyu)
        if(IWYU_EXECUTABLE)
            set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_EXECUTABLE}
                                               -Xiwyu --no_fwd_decls -Xiwyu --cxx17ns)
        endif()
    else()
        message(STATUS "Release build")
        set(CMAKE_BUILD_TYPE Release)
        list(APPEND CFLAGS_OPTIONS -s)
    endif()

    foreach(type ${TYPES})
        if(type STREQUAL "asan")
            message(STATUS "Add address sanitizer flags")
            list(APPEND LDFLAGS_OPTIONS -fsanitize=address -fno-omit-frame-pointer)
            list(APPEND CFLAGS_OPTIONS -fsanitize=address -fno-omit-frame-pointer)
        elseif(type STREQUAL "secu")
            message(STATUS "Add security flags")
            list(APPEND LDFLAGS_OPTIONS -Wl,-z,now -Wl,-z,relro -Wl,-z,noexecstack)
            list(APPEND CFLAGS_OPTIONS -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security
                                       -fstack-protector-all -Wstack-protector --param ssp-buffer-size=4
                                       -pie -fPIE -ftrapv)
        endif()
    endforeach()
endif()

# Adds options to the COMPILE_OPTIONS directory property.
# These options are used when compiling targets from the current
# directory and below. COMPILE_OPTIONS is the list of options to
# pass to the compiler
#
add_compile_options(${CFLAGS_OPTIONS})

# Add options to the link step for executable, shared library or
# module library targets in the current directory and below that
# are added after this command is invoked
#
add_link_options(${LDFLAGS_OPTIONS})
