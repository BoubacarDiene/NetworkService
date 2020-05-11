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
        parser/Parser.cpp
    PUBLIC
        executor/Executor.h
        parser/Parser.h
)
