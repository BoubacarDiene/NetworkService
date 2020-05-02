#include "utils/file/Writer.h"

#include "Setup.h"

using namespace service::plugins::network::layer;
using namespace service::plugins::logger;
using namespace utils::file;

struct Layer::Internal {
    const ILogger& logger;

    /* const to make the object non-copyable, non-movable and
     * non-resettable */
    const std::unique_ptr<Writer> writer;

    explicit Internal(const ILogger& providedLogger)
        : logger(providedLogger),
          writer(std::make_unique<Writer>(providedLogger))
    {}
};

Layer::Layer(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Layer::~Layer() = default;

void Layer::applyCommand(const std::string& pathname,
                         const std::string& value) const
{
    m_internal->logger.debug("Apply command: " + value + std::string(" > ")
                             + pathname);
    m_internal->writer->exec(pathname, value);
}
