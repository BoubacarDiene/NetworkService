#ifndef __UTILS_FILE_WRITER_H__
#define __UTILS_FILE_WRITER_H__

#include <memory>
#include <string>

#include "service/plugins/ILogger.h"

namespace utils::file {

class Writer {

public:
    explicit Writer(const service::plugins::logger::ILogger& logger);

    ~Writer();

    Writer(const Writer&) = delete;

    Writer& operator=(const Writer&) = delete;

    Writer(Writer&&) = delete;

    Writer& operator=(Writer&&) = delete;

    void exec(const std::string& pathname, const std::string& value) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
