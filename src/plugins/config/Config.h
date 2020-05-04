//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
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
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

#ifndef __PLUGINS_CONFIG_CONFIG_H__
#define __PLUGINS_CONFIG_CONFIG_H__

#include <memory>

#include "service/plugins/IConfig.h"
#include "service/plugins/ILogger.h"

namespace service::plugins::config {

class Config : public IConfig {

public:
    /**
     * logger made a const reference for better performances instead of
     * allowing this class to have its own copy of the logger (shared_ptr).
     * The counterpart is that the logger object must remain valid until
     * this class is no longer used.
     *
     * For example, the following code in "upper layer" where this class
     * is instantiated would make the service crash:
     *
     * // Declare config here
     * {
     *     // Initialize logger
     *     <type> logger = ...
     *     // Initialize Config
     *     config = Config(logger, ...)
     * }
     * // Using config here (out of scope) => crash because logger is not
     *    valid anymore.
     *
     * Passing std::shared_ptr by copy would solve that problem but it's
     * fine doing things this way because, by design, the plugins are part
     * of the lower-level details so the "upper layer" which instantiates
     * this class has to know how to properly use it
     */
    explicit Config(const service::plugins::logger::ILogger& logger);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~Config() override;

    Config(const Config&) = delete;

    Config& operator=(const Config&) = delete;

    Config(Config&&) = delete;

    Config& operator=(Config&&) = delete;

    [[nodiscard]] std::unique_ptr<ConfigData>
        load(const std::string& configFile) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
