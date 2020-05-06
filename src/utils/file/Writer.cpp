//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//                                                                                //
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2020 Boubacar DIENE                                              //
//                                                                                //
// This file is part of NetworkService project                                    //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
//                                                                                //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

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
