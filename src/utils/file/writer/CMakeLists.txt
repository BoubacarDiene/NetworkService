##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add writer in utils target
#
##

#################################################################
#                           Sources                             #
#################################################################

target_sources(${TARGET_UTILS_FILE_WRITER}
    PRIVATE
        Writer.cpp
    PUBLIC
        Writer.h
    INTERFACE
        IWriter.h
)
