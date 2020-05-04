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

#ifndef __PLUGINS_LOGGER_LOGGER_H__
#define __PLUGINS_LOGGER_LOGGER_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace service::plugins::logger {

class Logger : public ILogger {

public:
    explicit Logger();

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~Logger() override;

    Logger(const Logger&) = delete;

    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) = delete;

    Logger& operator=(Logger&&) = delete;

    void debug(const std::string& message) const override;

    void info(const std::string& message) const override;

    void warn(const std::string& message) const override;

    void error(const std::string& message) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
