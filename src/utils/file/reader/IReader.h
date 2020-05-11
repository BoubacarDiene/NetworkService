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

#ifndef __UTILS_FILE_IREADER_H__
#define __UTILS_FILE_IREADER_H__

#include <fstream>
#include <string>

namespace utils::file {

/**
 * @interface IReader IReader.h "utils/file/IReader.h"
 * @ingroup Helper
 *
 * @brief A helper class to read content from a specified input stream.
 *        This class is a high level interface added to ease testability
 *        of component that use it.
 *
 * @note Copy contructor, copy-assignment operator, move constructor and
 *       move-assignment operator are defined to be compliant with the
 *       "Rule of five"
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date May 2020
 */
class IReader {

public:
    /** Class constructor */
    IReader() = default;

    /** Class destructor */
    virtual ~IReader() = default;

    /** Class copy constructor */
    IReader(const IReader&) = delete;

    /** Class copy-assignment operator */
    IReader& operator=(const IReader&) = delete;

    /** Class move constructor */
    IReader(IReader&&) = delete;

    /** Class move-assignment operator */
    IReader& operator=(IReader&&) = delete;

    /**
     * @brief Read the content of the provided input stream and check errors
     *
     * Note that the stream must be opened before calling this method otherwise
     * an exception should be raised. Also, a path to a file (for example) is not
     * used in place of stream parameter to make possible unit testing without
     * reading from the filesystem.
     *
     * @param stream The input stream where to read data from
     * @param result The output variable into which the read data is stored
     */
    virtual void exec(std::istream& stream, std::string& result) const = 0;
};

}

#endif
