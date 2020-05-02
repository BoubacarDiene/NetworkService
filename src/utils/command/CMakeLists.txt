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
        Executor.cpp
        Parser.cpp
    PUBLIC
        Executor.h
        Parser.h
)
