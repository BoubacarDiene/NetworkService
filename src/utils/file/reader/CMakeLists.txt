##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add reader in utils target
#
##

#################################################################
#                           Sources                             #
#################################################################

target_sources(${TARGET_UTILS_FILE_READER}
    PRIVATE
        Reader.cpp
    PUBLIC
        Reader.h
    INTERFACE
        IReader.h
)
