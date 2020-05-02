#ifndef __SERVICE_PLUGINS_CONFIG_DATA_H__
#define __SERVICE_PLUGINS_CONFIG_DATA_H__

#include <map>
#include <string>
#include <vector>

namespace service::plugins::config {

struct ConfigData {
    struct Network {
        std::vector<std::string> interfaceNames;
        std::vector<std::string> interfaceCommands;
        std::map<std::string, std::string> layerCommands;
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
