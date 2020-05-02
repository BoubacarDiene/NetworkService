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
