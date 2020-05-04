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

#include <iostream>

#include "Logger.h"

#define BLUE   "\033[0;34m"
#define YELLOW "\033[1;33m"
#define RED    "\033[5;31m"
#define GREEN  "\033[0;32m"

#define END "\033[0m"

using namespace service::plugins::logger;

struct Logger::Internal {
    static void debug(const std::string& message,
                      const char* const color = BLUE)
    {
        std::cout << color << message << END << std::endl;
    }

    static void error(const std::string& message, const char* const color = RED)
    {
        std::cerr << color << message << END << std::endl;
    }
};

Logger::Logger() : m_internal(std::make_unique<Internal>()) {}

Logger::~Logger() = default;

void Logger::debug(const std::string& message) const
{
    Internal::debug(message);
}

void Logger::info(const std::string& message) const
{
    Internal::debug(message, GREEN);
}

void Logger::warn(const std::string& message) const
{
    Internal::debug(message, YELLOW);
}

void Logger::error(const std::string& message) const
{
    Internal::error(message);
}
