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
#                           Sources                             #
#################################################################

target_sources(${TARGET_UTILS_COMMAND}
    PRIVATE
        executor/Executor.cpp
        executor/osal/Linux.cpp
        parser/Parser.cpp
    PUBLIC
        executor/Executor.h
        executor/osal/Linux.h
        parser/Parser.h
    INTERFACE
        executor/IOsal.h
)
