##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to add mock in config target
#
##

#################################################################
#                           Sources                             #
#################################################################

target_sources(${TARGET_CONFIG_MOCK}
    PRIVATE
        MockReader.cpp
        MockReader.h
)
