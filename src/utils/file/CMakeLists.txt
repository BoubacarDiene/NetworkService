##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add file in utils target
#
##

#################################################################
#                           Sources                             #
#################################################################

target_sources(${TARGET_UTILS_FILE}
    PRIVATE
        writer/Writer.cpp
        writer/Writer.h
    INTERFACE
        writer/IWriter.h
)
