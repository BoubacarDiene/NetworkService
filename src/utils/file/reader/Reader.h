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

#ifndef __UTILS_FILE_READER_H__
#define __UTILS_FILE_READER_H__

#include <memory>

#include "service/plugins/ILogger.h"

#include "IReader.h"

namespace utils::file {

/**
 * @class Reader Reader.h "utils/file/Reader.h"
 * @ingroup Helper
 *
 * @brief A helper class to read content from a specified input stream
 *
 * This class is the "low level class" that implements @ref IReader.h
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
class Reader : public IReader {

public:
    /**
     * Class constructor
     *
     * @param logger Logger object to print some useful logs
     *
     * @note Instead of allowing this class to have its own copy of the logger
     *       object (shared_ptr), logger is made a non-const reference to a
     *       const object for better performances. The counterpart is that the
     *       logger object must (obviously) be kept valid by Main.cpp where it
     *       is created until this class is no longer used.
     */
    explicit Reader(const service::plugins::logger::ILogger& logger);

    /** Class destructor */
    ~Reader() override;

    /** Class copy constructor */
    Reader(const Reader&) = delete;

    /** Class copy-assignment operator */
    Reader& operator=(const Reader&) = delete;

    /** Class move constructor */
    Reader(Reader&&) = delete;

    /** Class move-assignment operator */
    Reader& operator=(Reader&&) = delete;

    /**
     * @brief Read content of provided input stream and check errors
     *
     * @param stream The input stream where to get data from
     * @param result The output variable into which store data
     */
    void readFromStream(std::istream& stream, std::string& result) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
