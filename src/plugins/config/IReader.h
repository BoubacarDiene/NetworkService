#ifndef __PLUGINS_CONFIG_IREADER_H__
#define __PLUGINS_CONFIG_IREADER_H__

#include <memory>

#include "service/plugins/IConfigData.h"

namespace service::plugins::config::reader {

class IReader {

public:
    IReader() = default;

    virtual ~IReader() = default;

    IReader(const IReader&) = delete;

    IReader& operator=(const IReader&) = delete;

    IReader(IReader&&) = delete;

    IReader& operator=(IReader&&) = delete;

    [[nodiscard]] virtual std::unique_ptr<service::plugins::config::ConfigData>
        readFrom(const std::string& configFile) const = 0;
};

}

#endif
