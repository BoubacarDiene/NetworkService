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

using namespace utils::file;

void Reader::readFromStream(std::istream& stream, std::string& result) const
{
    if (!stream.good()) {
        throw std::runtime_error("Reader: Invalid input stream");
    }

    // Get length of file
    stream.seekg(0, std::ios_base::end);
    std::streamoff length = stream.tellg();
    stream.seekg(0, std::ios_base::beg);

    // Technically, there's a potential data loss here but it is very unlikely
    // that uint64_t is not sufficient to contain the content of the whole stream.
    char* buffer = new char[static_cast<uint64_t>(length)];

    // Read data as a block
    // Note: operator>> is not used because it stops reading at first whitespace
    stream.read(buffer, length);

    if (stream.fail()) {
        delete[] buffer;

        std::stringstream readCharacters;
        readCharacters << stream.gcount() << "/" << length;
        throw std::runtime_error("Reader: Could not read all characters: "
                                 + readCharacters.str());
    }

    result.assign(buffer, static_cast<std::size_t>(length));
    delete[] buffer;
}
