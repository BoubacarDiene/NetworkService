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
 * \class IConfig
 * \ingroup Plugins
 *
 * \brief Provide the configuration used by the service to set up the network
 *
 * This class is the high level interface that must be implemented by all
 * network configuration provider(s). It is possible to retrieve the configu-
 * ration in various means:
 * - From a text file (.txt)
 * - From a JSON file (.jon)
 * - From a database (sqlite, ...)
 * - etc.
 *
 * The core service
 */

#ifndef __SERVICE_PLUGINS_ICONFIG_H__
#define __SERVICE_PLUGINS_ICONFIG_H__

#include <memory>

#include "IConfigData.h"

namespace service::plugins::config {

class IConfig {

public:
    IConfig() = default;

    virtual ~IConfig() = default;

    IConfig(const IConfig&) = delete;

    IConfig& operator=(const IConfig&) = delete;

    IConfig(IConfig&&) = delete;

    IConfig& operator=(IConfig&&) = delete;

    [[nodiscard]] virtual std::unique_ptr<ConfigData>
        load(const std::string& configFile) const = 0;
};

}

#endif
