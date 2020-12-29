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

#include <ios>
#include <sstream>
#include <stdexcept>

#include "Reader.h"

using namespace service::plugins::logger;
using namespace utils::file;

struct Reader::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}
};

Reader::Reader(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Reader::~Reader() = default;

void Reader::readFromStream(std::istream& stream, std::string& result) const
{
    if (!stream.good()) {
        throw std::runtime_error("Invalid input stream");
    }

    // Get length of file
    stream.seekg(0, std::ios_base::end);
    std::streamoff length = stream.tellg();
    stream.seekg(0, std::ios_base::beg);

    char* buffer = new char[length];

    // Read data as a block
    // Note: operator>> is not used because it stops reading at first whitespace
    stream.read(buffer, length);

    if (stream.fail()) {
        delete[] buffer;

        std::stringstream readCharacters;
        readCharacters << stream.gcount() << "/" << length;
        throw std::runtime_error("Could not read all characters: " + readCharacters.str());
    }

    result.assign(buffer, static_cast<std::size_t>(length));
    delete[] buffer;

    m_internal->logger.debug("Read: " + result);
}
