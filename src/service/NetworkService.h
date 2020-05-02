//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//  Copyright © 2020 Boubacar DIENE                                         //
//                                                                          //
//  This file is part of NetworkService project.                            //
//                                                                          //
//  NetworkService is free software: you can redistribute it and/or modify  //
//  it under the terms of the GNU General Public License as published by    //
//  the Free Software Foundation, either version 2 of the License, or       //
//  (at your option) any later version.                                     //
//                                                                          //
//  NetworkService is distributed in the hope that it will be useful,       //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//  GNU General Public License for more details.                            //
//                                                                          //
//  You should have received a copy of the GNU General Public License       //
//  along with NetworkService. If not, see <http://www.gnu.org/licenses/>   //
//  or write to the Free Software Foundation, Inc., 51 Franklin Street,     //
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/**
 * \defgroup Core Core service
 *
 * The core service is one of the most important components in this project
 * because it is responsible for loading the network configuration, set the
 * network up accordingly and also apply firewalling rules when relevant.
 *
 * To work properly, the core service relies on low level classes which
 * handle the implementation details (parsing, applying commands, ...).
 *
 * The core service has been designed so that it does not know anything
 * on how the work is really done below. Thus, it only depends on "stable"
 * abstractions called "plugins".
 *
 * @{
 */

/**
 * \defgroup Plugins
 * \ingroup Core
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
 * @{@}
 */

#ifndef __SERVICE_NETWORKSERVICE_H__
#define __SERVICE_NETWORKSERVICE_H__

#include "service/plugins/IConfig.h"
#include "service/plugins/ILogger.h"
#include "service/plugins/INetwork.h"
#include "service/plugins/IRuleFactory.h"

namespace service {

/**
 * \class NetworkServicce
 * \ingroup Core
 *
 * \brief Main class that directs operations
 *
 * Following a (kind of) Dependency Injection Principle, required objects
 * to interact with the plugins are provided to this class through its
 * constructor. Configuring the network and firewall is done in a certain
 * order and handling that is the main purpose of this class.
 *
 * \author Boubacar DIENE <boubacar.diene@gmail.com
 * \date April 2020
 */
class NetworkService {

public:
    /**
     * \brief Create a NetworkService object
     *
     * \param logger An object to use the logger plugin
     * \param config An object to use the config plugin
     * \param network An object to use the network plugin
     * \param ruleFactory An object to use the firewall plugin
     *
     * Note that passed-by-value smart pointers are used here. This choice is
     * well explained below:
     *
     * From
     * https://www.modernescpp.com/index.php/c-core-guidelines-passing-smart-pointer
     *
     * - R.32: Take a unique_ptr<widget> parameter to express that a function
     *   assumes ownership of a widget
     * - R.33: Take a unique_ptr<widget>& parameter to express that a function
     *   reseats the widget
     * - R.34: Take a shared_ptr<widget> parameter to express that a function
     *   is part owner
     * - R.35: Take a shared_ptr<widget>& parameter to express that a function
     *   might reseat the shared pointer
     * - R.36: Take a const shared_ptr<widget>& parameter to express that it
     *   might retain a reference count to the object
     *
     * How is that used here?
     *
     * logger:
     * - R.32 would force caller to transfer the ownership of this object to
     *   NetworkService (using std::move) making impossible for the caller to
     *   share it with others.
     *
     * - R.33 is not appropriate because NetworkService does not need to reset
     *   the object.
     *
     * - R.34 is fine because NetworkService also becomes an owner. Thus, even
     *   if others do not use their copy of the object anymore, that would not
     *   impact NetworkService's one. Also, I want NetworkService to be
     *   independent of the lower-level details.
     *
     *   Note: shared_ptr is known to add a little memory overhead due to the
     *   reference counter (see
     *   https://www.modernescpp.com/index.php/memory-and-performance-overhead-of-smart-pointer)
     *
     * - R.35, NO for the same reasons as R.33
     *
     * - R.36, better use a simple pointer or a reference to the object as
     *   mentioned in the article
     *
     *   R.34 wins!
     *
     * others:
     * - config, network and ruleFactory are expected to only have one single
     *   user i.e NetworkService so unique_ptr seems appropriate.
     * - NetworkService does not need to reset them so a non-const reference
     *   is not useful hence the choice of R.32 (by copy) which force the
     *   caller to transfer the ownership to NetworkService using std::move.
     */
    explicit NetworkService(
        std::shared_ptr<service::plugins::logger::ILogger> logger,
        std::unique_ptr<service::plugins::config::IConfig> config,
        std::unique_ptr<service::plugins::network::INetwork> network,
        std::unique_ptr<service::plugins::firewall::IRuleFactory> ruleFactory);

    /**
     * \brief Apply given network configuration in provided file
     *
     * \param configFile A valid path to a file in the filesystem containing
     *                   configuration to apply or any other specific data
     *                   the will be understood by the low level configuration
     *                   reader (E.g. database name, tables name, etc. in case
     *                   the config is retrieved from a database)
     * \return EXIT_SUCCESS on success, EXIT_FAILURE on failure
     */
    [[nodiscard]] int applyConfig(const std::string& configFile) const;

private:
    std::shared_ptr<service::plugins::logger::ILogger> m_logger;
    std::unique_ptr<service::plugins::config::IConfig> m_config;
    std::unique_ptr<service::plugins::network::INetwork> m_network;
    std::unique_ptr<service::plugins::firewall::IRuleFactory> m_ruleFactory;
};

}

#endif

/** @} */ // Core
