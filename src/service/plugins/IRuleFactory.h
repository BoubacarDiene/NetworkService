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

#ifndef __SERVICE_PLUGINS_IRULE_FACTORY_H__
#define __SERVICE_PLUGINS_IRULE_FACTORY_H__

#include <memory>
#include <string>
#include <vector>

#include "IRule.h"

namespace service::plugins::firewall {

class IRuleFactory {

public:
    IRuleFactory() = default;

    virtual ~IRuleFactory() = default;

    IRuleFactory(const IRuleFactory&) = delete;

    IRuleFactory& operator=(const IRuleFactory&) = delete;

    IRuleFactory(IRuleFactory&&) = delete;

    IRuleFactory& operator=(IRuleFactory&&) = delete;

    [[nodiscard]] virtual std::unique_ptr<IRule>
        createRule(const std::string& name,
                   const std::vector<std::string>& commands) const = 0;
};

}

#endif
