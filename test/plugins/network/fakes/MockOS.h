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

#ifndef __TEST_PLUGINS_NETWORK_FAKES_MOCK_OS_H__
#define __TEST_PLUGINS_NETWORK_FAKES_MOCK_OS_H__

#include <ifaddrs.h>
#include <sys/types.h>

#include "gmock/gmock.h"

namespace service::plugins::network {

class MockOS {

public:
    /** Class constructor */
    MockOS();

    /** Class destructor */
    ~MockOS();

    /** Copy constructor */
    MockOS(const MockOS&) = delete;

    /** Class copy-assignment operator */
    MockOS& operator=(const MockOS&) = delete;

    /** Class move constructor */
    MockOS(MockOS&&) = delete;

    /** Class move-assignment operator */
    MockOS& operator=(MockOS&&) = delete;

    /** Mocks */
    MOCK_METHOD(int, getifaddrs, (struct ifaddrs * *ifap));
    MOCK_METHOD(void, freeifaddrs, (struct ifaddrs * ifap));
};

}

#endif
