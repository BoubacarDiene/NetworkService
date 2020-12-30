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

#include "plugins/firewall/Rule.h"
#include "utils/command/parser/Parser.h"

using ::testing::_;

using namespace service::plugins::firewall;
using namespace utils::command;

namespace {

class RuleTestFixture : public ::testing::Test {

protected:
    MockExecutor m_mockExecutor;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(RuleTestFixture, shouldCallExecutorTwice)
{
    const std::string name("name");
    const std::vector<std::string> commands = {"command1", "command2"};

    Rule rule(name, commands, m_mockExecutor);

    EXPECT_CALL(m_mockExecutor, executeProgram(_)).Times(2);
    rule.applyCommands();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(RuleTestFixture, shouldCallExecutorWithExpectedValues)
{
    const std::string name("name");
    const std::vector<std::string> commands = {"command"};

    Rule rule(name, commands, m_mockExecutor);

    // Parser is deterministic meaning that for the same input, it will
    // always produce the same output so it's fine using it.
    const auto& parsedCommand = Parser::parse(commands[0]);
    const IExecutor::ProgramParams expectedParams
        = {parsedCommand->pathname, parsedCommand->argv, nullptr};

    EXPECT_CALL(m_mockExecutor, executeProgram(_))
        .WillOnce([&expectedParams](const IExecutor::ProgramParams& params) {
            ASSERT_STREQ(params.pathname, expectedParams.pathname);
            ASSERT_STREQ(params.argv[0], expectedParams.argv[0]);
            ASSERT_STREQ(params.argv[1], expectedParams.argv[1]);
        });

    rule.applyCommands();
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
