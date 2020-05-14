##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add command in utils target
#
##

#################################################################
#                       Subdirectories                          #
#################################################################

# Abstraction layer
# For now, conditional build is not necessary since only one OSAL
# exists
add_subdirectory(executor/osal)

#################################################################
#                           Sources                             #
#################################################################

# Parser and Executor could technically be separated but they are
# supposed to evolve together. Indeed, output of Parser is used as
# input for Executor
#
# => Built together until need for a separation becomes obvious
target_sources(${TARGET_UTILS_COMMAND}
    PRIVATE
        executor/Executor.cpp
        parser/Parser.cpp
    PUBLIC
        executor/Executor.h
        parser/Parser.h
        executor/IOsal.h
    INTERFACE
        executor/IExecutor.h
)
