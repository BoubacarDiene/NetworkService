##
#
# \file CMakeLists.txt
#
# \author Boubacar DIENE <boubacar.diene@gmail.com>
# \date   April 2020
#
# \brief  CMakeLists.txt to export public interfaces implemented
#         by the plugins. The core service depends on these and
#         not on their implementation so plugins could be updated
#         and deployed as many times as necessary, that would not
#         impact the service
#
##

#################################################################
#                          Interfaces                           #
#################################################################

# Config plugin
target_sources(${TARGET_PLUGINS_CONFIG}
    INTERFACE
        IConfig.h
        IConfigData.h
)

# Firewall plugin
target_sources(${TARGET_PLUGINS_FIREWALL}
    INTERFACE
        IRule.h
        IRuleFactory.h
)

# Logger plugin
target_sources(${TARGET_PLUGINS_LOGGER}
    INTERFACE
        ILogger.h
)

# Network plugin
target_sources(${TARGET_PLUGINS_NETWORK}
    INTERFACE
        INetwork.h
)
