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

#include "mocks/MockLogger.h"
#include "mocks/MockReader.h"

#include "plugins/config/Config.h"

using ::testing::AtLeast;
using ::testing::StartsWith;

using namespace service::plugins::logger;
using namespace service::plugins::config;
using namespace utils::file;

namespace {

class FakeConfigTestFixture : public ::testing::Test {

protected:
    FakeConfigTestFixture() : m_fakeConfig(m_mockLogger, m_mockReader)
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));
    }

    MockReader m_mockReader;
    MockLogger m_mockLogger;
    Config m_fakeConfig;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(FakeConfigTestFixture, shouldNotRelyOnAnyConfigFile)
{
    try {
        auto configData = m_fakeConfig.load("/fake/path/to/file");
        ASSERT_NE(configData, nullptr);
    }
    catch (const std::exception& e) {
        FAIL() << "FakeConfig is supposed to generate data itself without relying "
                  "on a file";
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(FakeConfigTestFixture, shouldNotGenerateTrueCommands)
{
    auto configData = m_fakeConfig.load("/fake/path/to/file");

    ASSERT_NE(configData, nullptr);

    // I'm interested in what the fake interfaceCommand does i.e just prints command
    // using "/bin/echo", not what it prints which, if updated, should not affect the
    // unit test
    for (const auto& interfaceCommand : configData->network.interfaceCommands) {
        EXPECT_THAT(interfaceCommand.c_str(), StartsWith("/bin/echo "));
    }

    // I want the fake layerCommand to write in "/dev/null" file; what is written is
    // not important here. The goal is to make sure that writing some text to a file
    // works.
    for (const auto& layerCommand : configData->network.layerCommands) {
        EXPECT_STREQ(layerCommand.pathname.c_str(), "/dev/null");
    }

    // Same as interfaceCommand: "/bin/echo" has to be used to print command
    for (const auto& rule : configData->rules) {
        for (const auto& command : rule.commands) {
            EXPECT_THAT(command.c_str(), StartsWith("/bin/echo "));
        }
    }
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
