#ifndef __SERVICE_PLUGINS_IRULE_H__
#define __SERVICE_PLUGINS_IRULE_H__

#include <string>
#include <vector>

namespace service::plugins::firewall {

class IRule {

public:
    IRule() = default;

    virtual ~IRule() = default;

    IRule(const IRule&) = delete;

    IRule& operator=(const IRule&) = delete;

    IRule(IRule&&) = delete;

    IRule& operator=(IRule&&) = delete;

    virtual void applyCommands() const = 0;
};

}

#endif
