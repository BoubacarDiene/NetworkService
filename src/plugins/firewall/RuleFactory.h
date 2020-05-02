#ifndef __PLUGINS_FIREWALL_RULE_FACTORY_H__
#define __PLUGINS_FIREWALL_RULE_FACTORY_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "service/plugins/IRuleFactory.h"

namespace service::plugins::firewall {

class RuleFactory : public IRuleFactory {

public:
    explicit RuleFactory(const service::plugins::logger::ILogger& logger);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~RuleFactory() override;

    RuleFactory(const RuleFactory&) = delete;

    RuleFactory& operator=(const RuleFactory&) = delete;

    RuleFactory(RuleFactory&&) = delete;

    RuleFactory& operator=(RuleFactory&&) = delete;

    [[nodiscard]] std::unique_ptr<IRule>
        createRule(const std::string& name,
                   const std::vector<std::string>& commands) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
