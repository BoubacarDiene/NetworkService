#ifndef __PLUGINS_CONFIG_MOCK_READER_H__
#define __PLUGINS_CONFIG_MOCK_READER_H__

#include "plugins/config/IReader.h"
#include "service/plugins/ILogger.h"

namespace service::plugins::config::reader {

class MockReader : public IReader {

public:
    explicit MockReader(const service::plugins::logger::ILogger& logger);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~MockReader() override;

    MockReader(const MockReader&) = delete;

    MockReader& operator=(const MockReader&) = delete;

    MockReader(MockReader&&) = delete;

    MockReader& operator=(MockReader&&) = delete;

    [[nodiscard]] std::unique_ptr<ConfigData>
        readFrom(const std::string& configFile) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
