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

#include "gtest/gtest.h"

#include "mocks/MockExecutor.h"
#include "mocks/MockLogger.h"

#include "plugins/firewall/RuleFactory.h"

using ::testing::AtLeast;

using namespace service::plugins::logger;
using namespace service::plugins::firewall;
using namespace utils::command;

namespace {

class RuleFactoryTestFixture : public ::testing::Test {

protected:
    RuleFactoryTestFixture() : m_ruleFactory(m_mockLogger, m_mockExecutor)
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));
    }

    MockExecutor m_mockExecutor;
    MockLogger m_mockLogger;
    RuleFactory m_ruleFactory;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(RuleFactoryTestFixture, createRuleShouldReturnAValidPointer)
{
    const std::string name("name");
    const std::vector<std::string> commands = {"command1", "command2"};

    ASSERT_NE(m_ruleFactory.createRule(name, commands), nullptr);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}