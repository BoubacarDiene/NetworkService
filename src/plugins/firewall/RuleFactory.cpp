#include "RuleFactory.h"
#include "Rule.h"

using namespace service::plugins::firewall;
using namespace service::plugins::logger;

struct RuleFactory::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}
};

RuleFactory::RuleFactory(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

RuleFactory::~RuleFactory() = default;

std::unique_ptr<IRule>
    RuleFactory::createRule(const std::string& name,
                            const std::vector<std::string>& commands) const
{
    m_internal->logger.debug("Create rule: " + name);
    return std::make_unique<Rule>(m_internal->logger, name, commands);
}
