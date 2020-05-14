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
#include "mocks/MockWriter.h"

#include "plugins/network/Network.h"

using ::testing::AtLeast;

using namespace service::plugins::config;
using namespace service::plugins::logger;
using namespace service::plugins::network;
using namespace utils::command;
using namespace utils::file;

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

    MockExecutor m_mockExecutor;
    MockWriter m_mockWriter;
    Network m_network;

private:
    MockLogger m_mockLogger;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, hasInterfaceReturnTrueIfInterfaceExists)
{
    ASSERT_TRUE(m_network.hasInterface("lo"));
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, hasInterfaceReturnFalseIfInterfaceDoesNotExist)
{
    ASSERT_FALSE(m_network.hasInterface("doesNotExist"));
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, applyInterfaceCommandsShouldNotFailWithValidParameters)
{
    const std::vector<std::string> interfaceCommands = {"command1", "command2"};
    m_network.applyInterfaceCommands(interfaceCommands);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkTestFixture, applyLayerCommandsShouldNotFailWithValidParameters)
{
    const std::vector<ConfigData::Network::LayerCommand> layerCommands
        = {{"pathname1", "value1"}, {"pathname2", "value2"}};
    m_network.applyLayerCommands(layerCommands);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
