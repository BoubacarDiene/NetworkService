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

#ifndef __TEST_MOCKS_MOCK_LOGGER_H__
#define __TEST_MOCKS_MOCK_LOGGER_H__

#include "gmock/gmock.h"

#include "service/plugins/ILogger.h"

namespace service::plugins::logger {

class MockLogger : public ILogger {

public:
    /** Class constructor */
    MockLogger();

    /** Class destructor */
    ~MockLogger() override;

    /** Copy constructor */
    MockLogger(const MockLogger&) = delete;

    /** Class copy-assignment operator */
    MockLogger& operator=(const MockLogger&) = delete;

    /** Class move constructor */
    MockLogger(MockLogger&&) = delete;

    /** Class move-assignment operator */
    MockLogger& operator=(MockLogger&&) = delete;

    /** Mocks */
    MOCK_METHOD(void, debug, (const std::string& message), (const, override));
    MOCK_METHOD(void, info, (const std::string& message), (const, override));
    MOCK_METHOD(void, warn, (const std::string& message), (const, override));
    MOCK_METHOD(void, error, (const std::string& message), (const, override));
};

}

#endif
