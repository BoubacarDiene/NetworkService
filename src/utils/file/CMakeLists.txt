##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add files in utils target
#
##

#################################################################
#                           Sources                             #
#################################################################

target_sources(${TARGET_UTILS_FILE}
    PRIVATE
        reader/Reader.cpp
        reader/Reader.h
        writer/Writer.cpp
        writer/Writer.h
    INTERFACE
        reader/IReader.h
        writer/IWriter.h
)
