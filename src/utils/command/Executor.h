#ifndef __UTILS_COMMAND_EXECUTOR_H__
#define __UTILS_COMMAND_EXECUTOR_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace utils::command {

class Executor {

public:
    enum Flags : unsigned int {
        WAIT_COMMAND    = (1u << 0u),
        RESEED_PRNG     = (1u << 1u),
        SANITIZE_FILES  = (1u << 2u),
        DROP_PRIVILEGES = (1u << 3u),
        ALL = (WAIT_COMMAND | RESEED_PRNG | SANITIZE_FILES | DROP_PRIVILEGES)
    };

    explicit Executor(const service::plugins::logger::ILogger& logger);

    ~Executor();

    Executor(const Executor&) = delete;

    Executor& operator=(const Executor&) = delete;

    Executor(Executor&&) = delete;

    Executor& operator=(Executor&&) = delete;

    void exec(const char* pathname,
              char* const argv[],
              char* const envp[],
              Flags flags = Flags::ALL) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
