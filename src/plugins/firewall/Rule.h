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

#ifndef __PLUGINS_FIREWALL_RULE_H__
#define __PLUGINS_FIREWALL_RULE_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "service/plugins/IRule.h"

namespace service::plugins::firewall {

class Rule : public IRule {

public:
    explicit Rule(const service::plugins::logger::ILogger& logger,
                  const std::string& name,
                  const std::vector<std::string>& commands);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~Rule() override;

    Rule(const Rule&) = delete;

    Rule& operator=(const Rule&) = delete;

    Rule(Rule&&) = delete;

    Rule& operator=(Rule&&) = delete;

    void applyCommands() const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
