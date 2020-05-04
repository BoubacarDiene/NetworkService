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

#include "utils/file/Writer.h"

#include "Setup.h"

using namespace service::plugins::network::layer;
using namespace service::plugins::logger;
using namespace utils::file;

struct Layer::Internal {
    const ILogger& logger;

    /* const to make the object non-copyable, non-movable and
     * non-resettable */
    const std::unique_ptr<Writer> writer;

    explicit Internal(const ILogger& providedLogger)
        : logger(providedLogger),
          writer(std::make_unique<Writer>(providedLogger))
    {}
};

Layer::Layer(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Layer::~Layer() = default;

void Layer::applyCommand(const std::string& pathname,
                         const std::string& value) const
{
    m_internal->logger.debug("Apply command: " + value + std::string(" > ")
                             + pathname);
    m_internal->writer->exec(pathname, value);
}
