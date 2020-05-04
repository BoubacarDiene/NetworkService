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

#include <fstream>
#include <stdexcept>
#include <sys/stat.h>

#include "Writer.h"

using namespace service::plugins::logger;
using namespace utils::file;

struct Writer::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    /**
     * Check if a file exists
     * @return true if and only if the file exists, false otherwise
     */
    static bool fileExists(const std::string& pathname)
    {
        struct stat buffer;
        return (stat(pathname.c_str(), &buffer) == 0);
    }
};

Writer::Writer(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Writer::~Writer() = default;

void Writer::exec(const std::string& pathname, const std::string& value) const
{
    if (!m_internal->fileExists(pathname)) {
        m_internal->logger.error(pathname + " not found");
        throw std::invalid_argument(pathname + " not found");
    }

    std::ofstream ofs(pathname);
    ofs << value;
    ofs.close();

    m_internal->logger.debug(value + " written to " + pathname);
}
