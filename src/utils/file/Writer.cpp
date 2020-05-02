#include <fstream>
#include <stdexcept>
#include <sys/stat.h>

#include "Writer.h"

using namespace service::plugins::logger;
using namespace utils::file;

struct Writer::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    /**
     * Check if a file exists
     * @return true if and only if the file exists, false otherwise
     */
    static bool fileExists(const std::string& pathname)
    {
        struct stat buffer;
        return (stat(pathname.c_str(), &buffer) == 0);
    }
};

Writer::Writer(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Writer::~Writer() = default;

void Writer::exec(const std::string& pathname, const std::string& value) const
{
    if (!m_internal->fileExists(pathname)) {
        m_internal->logger.error(pathname + " not found");
        throw std::invalid_argument(pathname + " not found");
    }

    std::ofstream ofs(pathname);
    ofs << value;
    ofs.close();

    m_internal->logger.debug(value + " written to " + pathname);
}
