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
