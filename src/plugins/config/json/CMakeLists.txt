##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add json in config target
#
##

#################################################################
#                           Sources                             #
#################################################################

target_sources(${TARGET_CONFIG_JSON}
    PRIVATE
        JsonReader.cpp
        JsonReader.h
)
