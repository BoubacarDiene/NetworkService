#include <cstring>

#include "Errno.h"

using namespace utils::helper;

std::string Errno::toString(const char* whichCall, int error)
{
    return std::string(whichCall) + ": " + std::strerror(error);
}
