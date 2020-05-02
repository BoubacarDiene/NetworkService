#ifndef __PLUGINS_CONFIG_JSON_READER_H__
#define __PLUGINS_CONFIG_JSON_READER_H__

#include "plugins/config/IReader.h"
#include "service/plugins/ILogger.h"

namespace service::plugins::config::reader {

class JsonReader : public IReader {

public:
    explicit JsonReader(const service::plugins::logger::ILogger& logger);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~JsonReader() override;

    JsonReader(const JsonReader&) = delete;

    JsonReader& operator=(const JsonReader&) = delete;

    JsonReader(JsonReader&&) = delete;

    JsonReader& operator=(JsonReader&&) = delete;

    [[nodiscard]] std::unique_ptr<ConfigData>
        readFrom(const std::string& configFile) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
