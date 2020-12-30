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

#include "fakes/MockOS.h"
#include "mocks/MockExecutor.h"
#include "mocks/MockLogger.h"
#include "mocks/MockWriter.h"

#include "plugins/network/Network.h"
#include "utils/command/parser/Parser.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

using namespace service::plugins::config;
using namespace service::plugins::logger;
using namespace service::plugins::network;
using namespace utils::command;
using namespace utils::file;

MockOS* gMockOS = nullptr;

namespace {

class NetworkTestFixture : public ::testing::Test {

protected:
    NetworkTestFixture() : m_network(m_mockLogger, m_mockExecutor, m_mockWriter)
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));
    }

    void SetUp() override
    {
        gMockOS = &m_mockOS;
    }

    void TearDown() override
    {
        gMockOS = nullptr;
    }

    MockLogger m_mockLogger;
    MockExecutor m_mockExecutor;
    MockWriter m_mockWriter;
    Network m_network;

    MockOS m_mockOS;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, hasInterfaceRaisesExceptionIfGetIfaddrsFails)
{
    EXPECT_CALL(m_mockOS, getifaddrs).WillOnce(Return(-1));

    try {
        (void)m_network.hasInterface("fakeInterface");
        FAIL() << "Should fail because getifaddrs() has failed";
    }
    catch (const std::runtime_error& e) {
        // Expected!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, hasInterfaceReturnTrueIfInterfaceExists)
{
    struct sockaddr ifaAddr;
    struct ifaddrs ifaNext;
    struct ifaddrs firstIfaAddr;

    char interface[] = "fakeInterface";

    firstIfaAddr.ifa_next = &ifaNext;
    firstIfaAddr.ifa_name = nullptr;
    firstIfaAddr.ifa_addr = nullptr;

    firstIfaAddr.ifa_next->ifa_name            = static_cast<char*>(interface);
    firstIfaAddr.ifa_next->ifa_addr            = &ifaAddr;
    firstIfaAddr.ifa_next->ifa_addr->sa_family = AF_PACKET;

    EXPECT_CALL(m_mockOS, getifaddrs)
        .WillOnce([&firstIfaAddr](struct ifaddrs** ifap) {
            *ifap = &firstIfaAddr;
            return 0;
        });

    EXPECT_CALL(m_mockOS, freeifaddrs).Times(1);

    ASSERT_TRUE(m_network.hasInterface("fakeInterface"));
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, hasInterfaceReturnFalseIfInterfaceDoesNotExist)
{
    EXPECT_CALL(m_mockOS, getifaddrs).WillOnce(Return(0));
    EXPECT_CALL(m_mockOS, freeifaddrs).Times(1);

    ASSERT_FALSE(m_network.hasInterface("doesNotExist"));
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, applyInterfaceCommandsShouldNotFailWithValidParameters)
{
    const std::vector<std::string> interfaceCommands = {"command"};

    // Parser is deterministic meaning that for the same input, it will
    // always produce the same output so it's fine using it.
    const auto& parsedCommand = Parser(m_mockLogger).parse(interfaceCommands[0]);
    const IExecutor::ProgramParams expectedParams
        = {parsedCommand->pathname, parsedCommand->argv, nullptr};

    EXPECT_CALL(m_mockExecutor, executeProgram(_))
        .WillOnce([&expectedParams](const IExecutor::ProgramParams& params) {
            ASSERT_STREQ(params.pathname, expectedParams.pathname);
            ASSERT_STREQ(params.argv[0], expectedParams.argv[0]);
            ASSERT_STREQ(params.argv[1], expectedParams.argv[1]);
        });

    m_network.applyInterfaceCommands(interfaceCommands);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, applyLayerCommandsShouldNotFailWithValidParameters)
{
    const std::vector<ConfigData::Network::LayerCommand> layerCommands
        = {{"pathname", "value"}};
    const std::string expectedValue("value");

    EXPECT_CALL(m_mockWriter, writeToStream(_, _))
        .WillOnce([&expectedValue]([[maybe_unused]] std::ostream& stream,
                                   const std::string& value) {
            ASSERT_EQ(value, expectedValue);
        });

    m_network.applyLayerCommands(layerCommands);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
