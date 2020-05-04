#ifndef __SERVICE_PLUGINS_CONFIG_DATA_H__
#define __SERVICE_PLUGINS_CONFIG_DATA_H__

#include <string>
#include <vector>

namespace service::plugins::config {

struct ConfigData {
    struct Network {
        struct LayerCommand {
            std::string pathname;
            std::string value;
        };

        std::vector<std::string> interfaceNames;
        std::vector<std::string> interfaceCommands;
        std::vector<LayerCommand> layerCommands;
    };

    struct Rule {
        std::string name;
        std::vector<std::string> commands;
    };

    Network network;
    std::vector<Rule> rules;
};

}

#endif
