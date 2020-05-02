#include "MockReader.h"

using namespace service::plugins::config;
using namespace service::plugins::config::reader;
using namespace service::plugins::logger;

struct MockReader::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    static void fillInConfigData(const std::string& configFile,
                                 std::unique_ptr<ConfigData>& configData)
    {
        /* Instead of "forwarding" configFile, a real config reader could, for
         * example, open it to obtain a valid stream to retrieve data from.
         *
         * Besides, unlike to other config generators, configFile is a fake
         * config file i.e no config is loaded from there. Nevertheless, the
         * file exists in the filesystem so it is used here to store output of
         * some commands */
        fillInNetworkData(configFile, &configData->network);
        fillInRulesData(configFile, &configData->rules);
    }

private:
    static void fillInNetworkData(const std::string& configFile,
                                  ConfigData::Network* network)
    {
        network->interfaceNames.emplace_back("lo");

        network->interfaceCommands.emplace_back(
            "/bin/echo \"[MOCK] Interface command 1\n\" >> " + configFile);
        network->interfaceCommands.emplace_back(
            "/bin/echo \"[MOCK] Interface command 2\n\" >> " + configFile);

        network->layerCommands.insert({configFile, "[MOCK] Layer: value\n"});
    }

    static void fillInRulesData(const std::string& configFile,
                                std::vector<ConfigData::Rule>* rules)
    {
        std::vector<std::string> rule1Commands
            = {"/bin/echo \"[MOCK] Rule 1: command 1\n\" >> " + configFile,
               "/bin/echo \"[MOCK] Rule 1: command 2\n\" >> " + configFile};
        rules->emplace_back(ConfigData::Rule({"Rule 1", rule1Commands}));

        std::vector<std::string> rule2Commands
            = {"/bin/echo \"[MOCK] Rule 2: command 1\n\" >> " + configFile};
        rules->emplace_back(ConfigData::Rule({"Rule 2", rule2Commands}));
    }
};

MockReader::MockReader(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

MockReader::~MockReader() = default;

std::unique_ptr<ConfigData>
    MockReader::readFrom(const std::string& configFile) const
{
    std::unique_ptr<ConfigData> configData = std::make_unique<ConfigData>();

    m_internal->logger.debug("Fill in config data");
    Internal::fillInConfigData(configFile, configData);

    return configData;
}
