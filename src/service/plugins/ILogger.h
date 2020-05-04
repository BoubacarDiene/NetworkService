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

#ifndef __SERVICE_PLUGINS_ILOGGER_H__
#define __SERVICE_PLUGINS_ILOGGER_H__

#include <string>

namespace service::plugins::logger {

class ILogger {

public:
    ILogger() = default;

    virtual ~ILogger() = default;

    ILogger(const ILogger&) = delete;

    ILogger& operator=(const ILogger&) = delete;

    ILogger(ILogger&&) = delete;

    ILogger& operator=(ILogger&&) = delete;

    /**
     * One purpose in marking these member functions as const is that
     * a const pointer or reference to ILogger can be used to call them.
     * Thus, one can get "const ILogger*" or "const ILogger&" as input
     * if neighter a reset of the logger object, nor becoming an owner
     * of it is necessary.
     *
     * Without this const, one would be forced to use "ILogger*" or
     * "ILogger&" in that case thus have possibility to alter the
     * logger object which is not what is expected.
     */
    virtual void debug(const std::string& message) const = 0;

    virtual void info(const std::string& message) const = 0;

    virtual void warn(const std::string& message) const = 0;

    virtual void error(const std::string& message) const = 0;
};

}

#endif
