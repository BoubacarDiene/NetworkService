//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//                                                                                //
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2020 Boubacar DIENE                                              //
//                                                                                //
// This file is part of NetworkService project                                    //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
//                                                                                //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

#include <ifaddrs.h>
#include <stdexcept>
#include <sys/types.h>

#include "utils/helper/Errno.h"

#include "interface/Setup.h"
#include "layer/Setup.h"

#include "Network.h"

using namespace service::plugins::config;
using namespace service::plugins::logger;
using namespace service::plugins::network;
using namespace service::plugins::network::interface;
using namespace service::plugins::network::layer;
using namespace utils::helper;

struct Network::Internal {
    const ILogger& logger;
    const Interface interface;
    const Layer layer;

    explicit Internal(const ILogger& providedLogger,
                      const utils::command::IExecutor& providedExecutor,
                      const utils::file::IWriter& providedWriter)
        : logger(providedLogger),
          interface(Interface(logger, providedExecutor)),
          layer(Layer(providedLogger, providedWriter))
    {}
};

Network::Network(const ILogger& logger,
                 const utils::command::IExecutor& executor,
                 const utils::file::IWriter& writer)
    : m_internal(std::make_unique<Internal>(logger, executor, writer))
{}

Network::~Network() = default;

bool Network::hasInterface(const std::string& interfaceName) const
{
    bool exist           = false;
    ifaddrs* ifaddresses = nullptr;

    if (getifaddrs(&ifaddresses) == -1) {
        throw std::runtime_error(Errno::toString("getifaddrs()", errno));
    }

    for (const auto* ifa = ifaddresses; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) {
            continue;
        }

        if ((ifa->ifa_addr->sa_family == AF_PACKET)
            && (interfaceName == ifa->ifa_name)) {
            m_internal->logger.debug("Interface exists: " + interfaceName);
            exist = true;
            break;
        }
    }

    freeifaddrs(ifaddresses);

    return exist;
}

void Network::applyInterfaceCommands(
    const std::vector<std::string>& interfaceCommands) const
{
    for (const std::string& interfaceCommand : interfaceCommands) {
        m_internal->logger.debug("Apply interface command: " + interfaceCommand);
        m_internal->interface.applyCommand(interfaceCommand);
    }
}

void Network::applyLayerCommands(
    const std::vector<ConfigData::Network::LayerCommand>& layerCommands) const
{
    for (const auto& layerCommand : layerCommands) {
        m_internal->logger.debug("Apply layer command to: " + layerCommand.pathname);
        m_internal->layer.applyCommand(layerCommand.pathname, layerCommand.value);
    }
}
