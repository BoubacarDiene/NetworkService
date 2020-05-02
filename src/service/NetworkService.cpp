#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <utility>

#include "NetworkService.h"

using namespace service;
using namespace service::plugins::config;
using namespace service::plugins::firewall;
using namespace service::plugins::logger;
using namespace service::plugins::network;

// std::move is used on logger for performances's sake. Indeed, logger is
// passed by copy => +1 on reference counter.
// Without std::move, +1 again on reference counter so it is better to use
// std::move here to move the ownership of NetworkService's copy of logger
// object to its internal member object (m_logger).
//
// For others (unique_ptr), std::move is required because the constructor
// does not just use provided objects. It also keeps copies.
NetworkService::NetworkService(std::shared_ptr<ILogger> logger,
                               std::unique_ptr<IConfig> config,
                               std::unique_ptr<INetwork> network,
                               std::unique_ptr<IRuleFactory> ruleFactory)
    : m_logger(std::move(logger)),
      m_config(std::move(config)),
      m_network(std::move(network)),
      m_ruleFactory(std::move(ruleFactory))
{}

int NetworkService::applyConfig(const std::string& configFile) const
{
    try {
        m_logger->debug("Load config: " + configFile);
        const std::unique_ptr<ConfigData>& configData
            = m_config->load(configFile);

        m_logger->debug("Make sure specified interfaces are valid");
        const ConfigData::Network& networkData         = configData->network;
        const std::vector<ConfigData::Rule>& rulesData = configData->rules;

        for (const std::string& interfaceName : networkData.interfaceNames) {
            if (!m_network->hasInterface(interfaceName)) {
                throw std::invalid_argument("No valid interface found for: "
                                            + interfaceName);
            }
        }

        m_logger->debug("Apply network interface commands");
        m_network->applyInterfaceCommands(networkData.interfaceCommands);

        m_logger->debug("Apply network layer commands");
        m_network->applyLayerCommands(networkData.layerCommands);

        m_logger->debug("Create and apply rules");
        for (const ConfigData::Rule& ruleData : rulesData) {
            const std::unique_ptr<IRule>& rule
                = m_ruleFactory->createRule(ruleData.name, ruleData.commands);
            rule->applyCommands();
        }
    }
    catch (const std::exception& e) {
        // All exceptions are caught because the service is expected to ignore
        // how lower -level components are implemented (which specific exception
        // is raised, ...)
        m_logger->error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
