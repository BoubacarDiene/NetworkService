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

#ifndef __TEST_MOCKS_MOCK_CONFIG_H__
#define __TEST_MOCKS_MOCK_CONFIG_H__

#include "gmock/gmock.h"

#include "service/plugins/IConfig.h"

namespace service::plugins::config {

class MockConfig : public IConfig {

public:
    /** Class constructor */
    MockConfig();

    /** Class destructor */
    ~MockConfig() override;

    /** Copy constructor */
    MockConfig(const MockConfig&) = delete;

    /** Class copy-assignment operator */
    MockConfig& operator=(const MockConfig&) = delete;

    /** Class move constructor */
    MockConfig(MockConfig&&) = delete;

    /** Class move-assignment operator */
    MockConfig& operator=(MockConfig&&) = delete;

    /** Mocks */
    MOCK_METHOD(std::unique_ptr<ConfigData>,
                load,
                (const std::string& configFile),
                (const, override));
};

}

#endif
