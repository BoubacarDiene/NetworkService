#ifndef __UTILS_HELPER_ERRNO_H__
#define __UTILS_HELPER_ERRNO_H__

#include <string>

namespace utils::helper {

class Errno {

public:
    static std::string toString(const char* whichCall, int error);
};

}

#endif
