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

#ifndef __SERVICE_NETWORKSERVICE_H__
#define __SERVICE_NETWORKSERVICE_H__

#include "service/plugins/IConfig.h"
#include "service/plugins/ILogger.h"
#include "service/plugins/INetwork.h"
#include "service/plugins/IRuleFactory.h"

namespace service {

/**
 * @defgroup Core Core service
 *
 * The core service is one of the most important components in this project
 * because it is responsible for loading the network configuration, setting
 * the network up accordingly and also apply firewalling rules when relevant.
 *
 * To work properly, the core service relies on low level classes which
 * handle the implementation details (parsing, applying commands, ...).
 *
 * The core service has been designed so that it does not know anything
 * on how the work is really done below. Thus, it only depends on "stable"
 * abstractions implemented by what are called "plugins".
 *
 * @{
 *
 * @defgroup Plugins Plugins
 *
 * Plugins are a set of components that concretize those "stable" abstractions
 * on which depends the core service. They implement the interfaces managed by
 * the core service (Config, Network, Logger, ...).
 *
 * For example, when the core service needs to print some debugging logs, it
 * just performs a function call (always the same) which is handled by the
 * logger plugin. This latter can then "decide" to print the logs to the
 * standard output, a log file, a database, etc. depending on what has been
 * been implemented.
 *
 * This design allows the core service to be extensible without any change in
 * its source code (Open Closed Principle).
 *
 * @{
 *
 * @defgroup Abstraction Abstraction
 *
 * This group is composed of abstract/high level classes.
 * High level classes have been created to give the core service possibility
 * to depend on something "stable" i.e that is not supposed to change a lot.
 * By depending on these abstract classes, the core service can also easily
 * be extended by just adding new code thus keeping the already tested code
 * unchanged.
 *
 * @{@}
 *
 * @defgroup Implementation Implementation
 *
 * This group is composed of low level details the core service should not
 * be aware of. Indeed, here are implemented all abstract classes described
 * in @ref Abstraction.
 *
 * @{
 *
 * @defgroup Helper Helper
 *
 * This group is composed of a set of helper classes needed by plugins to
 * handle tasks more easily.
 *
 * @{@}
 *
 * @} //Implementation
 *
 * @} //Plugins
 *
 * @} //Core
 */

/**
 * @class NetworkService NetworkService.h "service/NetworkService.h"
 * @ingroup Core
 *
 * @brief Main class that directs operations
 *
 * Following a (kind of) Dependency Injection Principle, required objects
 * to interact with the plugins are provided to this class through its
 * constructor. Configuring the network and firewall is done in a certain
 * order and handling that is the main purpose of this class.
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
class NetworkService {

public:
    /**
     * @struct NetworkServiceParams
     *
     * @brief A data structure containing all input parameters expected by the
     *        construtor.
     *
     * One reason that explains why a structure is preferred over a long list of
     * input parameters (>=4) is that this way it is easier to add new parameters
     * without impacting the readability.
     */
    struct NetworkServiceParams {
        /** An object to use the logger plugin */
        const plugins::logger::ILogger& logger;

        /** An object to use the config plugin */
        const plugins::config::IConfig& config;

        /** An object to use the network plugin */
        const plugins::network::INetwork& network;

        /** An object to use the firewall plugin */
        const plugins::firewall::IRuleFactory& ruleFactory;
    };

    /**
     * @brief Create a NetworkService object
     *
     * @param params A structure of type @ref NetworkServiceParams with all
     *               expected parameters
     */
    explicit NetworkService(const NetworkServiceParams& params);

    /**
     * @brief Apply the network configuration given in provided file
     *
     * @param configFile A valid path to a file in the filesystem containing
     *                   configuration to apply or any other specific data
     *                   the will be understood by the low level configuration
     *                   reader (E.g. database name, tables name, etc. in case
     *                   the config is retrieved from a database)
     *
     * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
     */
    [[nodiscard]] int applyConfig(const std::string& configFile) const;

private:
    const NetworkServiceParams& m_params;
};

/**@}*/

}

#endif
