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

#ifndef __TEST_MOCKS_MOCK_OSAL_H__
#define __TEST_MOCKS_MOCK_OSAL_H__

#include "gmock/gmock.h"

#include "utils/command/executor/IOsal.h"

namespace utils::command::osal {

class MockOsal : public IOsal {

public:
    /** Class constructor */
    MockOsal();

    /** Class destructor */
    ~MockOsal() override;

    /** Copy constructor */
    MockOsal(const MockOsal&) = delete;

    /** Class copy-assignment operator */
    MockOsal& operator=(const MockOsal&) = delete;

    /** Class move constructor */
    MockOsal(MockOsal&&) = delete;

    /** Class move-assignment operator */
    MockOsal& operator=(MockOsal&&) = delete;

    /** Mocks */
    MOCK_METHOD(ProcessId, createProcess, (), (const, override));
    MOCK_METHOD(void, waitChildProcess, (), (const, override));
    MOCK_METHOD(void,
                executeProgram,
                (const char* pathname, char* const argv[], char* const envp[]),
                (const, override));
    MOCK_METHOD(void, reseedPRNG, (), (const, override));
    MOCK_METHOD(void, sanitizeFiles, (), (const, override));
    MOCK_METHOD(void, dropPrivileges, (), (const, override));
};

}

#endif
