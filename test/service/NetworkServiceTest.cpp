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

#include "mocks/MockConfig.h"
#include "mocks/MockLogger.h"
#include "mocks/MockNetwork.h"
#include "mocks/MockRule.h"
#include "mocks/MockRuleFactory.h"

#include "service/NetworkService.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::ByMove;
using ::testing::Return;
using ::testing::Sequence;
using ::testing::Throw;

using namespace service;
using namespace service::plugins::logger;
using namespace service::plugins::config;
using namespace service::plugins::network;
using namespace service::plugins::firewall;

namespace {

class NetworkServiceTestFixture : public ::testing::Test {

private:
    NetworkService::NetworkServiceParams m_networkServiceParams;

protected:
    NetworkServiceTestFixture()
        : m_networkServiceParams(
            {m_mockLogger, m_mockConfig, m_mockNetwork, m_mockRuleFactory}),
          m_networkService(m_networkServiceParams)
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));

        // Prepare returned values
        ConfigData configData
            = {{{"interfaceName1", "interfaceName2"},
                {"interfaceCommand1", "interfaceCommand2"},
                {{"pathname1", "value1"}, {"pathname2", "value2"}}},
               {{"ruleName", {"command1", "command2"}}}};

        ON_CALL(m_mockConfig, load(_))
            .WillByDefault(Return(ByMove(std::make_unique<ConfigData>(configData))));
    }

    MockLogger m_mockLogger;
    MockConfig m_mockConfig;
    MockNetwork m_mockNetwork;
    MockRuleFactory m_mockRuleFactory;

    NetworkService m_networkService;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, returnFailureWhenLoadRaisesAnException)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile))
        .WillOnce(Throw(std::runtime_error("Exception")));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, returnFailureWhenHasInterfaceReturnFalse)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface).WillOnce(Return(false));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, returnFailureWhenHasInterfaceRaisesAnException)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface)
        .WillOnce(Throw(std::runtime_error("Exception")));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture,
       returnFailureWhenApplyInterfaceCommandsRaisesAnException)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface).WillRepeatedly(Return(true));
    EXPECT_CALL(m_mockNetwork, applyLayerCommands).Times(AtLeast(0));

    EXPECT_CALL(m_mockNetwork, applyInterfaceCommands)
        .WillOnce(Throw(std::runtime_error("Exception")));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture,
       returnFailureWhenApplyLayerCommandsRaisesAnException)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface).WillRepeatedly(Return(true));
    EXPECT_CALL(m_mockNetwork, applyInterfaceCommands).Times(AtLeast(0));

    EXPECT_CALL(m_mockNetwork, applyLayerCommands)
        .WillOnce(Throw(std::runtime_error("Exception")));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, returnFailureWhenCreateRuleRaisesAnException)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface).WillRepeatedly(Return(true));
    EXPECT_CALL(m_mockNetwork, applyInterfaceCommands).Times(AtLeast(0));
    EXPECT_CALL(m_mockNetwork, applyLayerCommands).Times(AtLeast(0));

    EXPECT_CALL(m_mockRuleFactory, createRule)
        .WillOnce(Throw(std::runtime_error("Exception")));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, returnFailureWhenCreateRuleReturnNull)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface).WillRepeatedly(Return(true));
    EXPECT_CALL(m_mockNetwork, applyInterfaceCommands);
    EXPECT_CALL(m_mockNetwork, applyLayerCommands);

    EXPECT_CALL(m_mockRuleFactory, createRule);

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, hasInterfaceShouldBeCalledTwice)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);
    EXPECT_CALL(m_mockNetwork, hasInterface)
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_FAILURE);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(NetworkServiceTestFixture, setupNetworkBeforeFirewall)
{
    std::string configFile("/path/to/configFile");

    EXPECT_CALL(m_mockConfig, load(configFile)).Times(1);

    {
        Sequence seq1;
        Sequence seq2;

        EXPECT_CALL(m_mockNetwork, hasInterface)
            .InSequence(seq1, seq2)
            .WillRepeatedly(Return(true));
        EXPECT_CALL(m_mockNetwork, applyInterfaceCommands).InSequence(seq1);
        EXPECT_CALL(m_mockNetwork, applyLayerCommands).InSequence(seq2);
        EXPECT_CALL(m_mockRuleFactory, createRule)
            .InSequence(seq2)
            .WillOnce([]([[maybe_unused]] const std::string& name,
                         [[maybe_unused]] const std::vector<std::string>& commands) {
                auto rule = std::make_unique<MockRule>();
                EXPECT_CALL(*rule, applyCommands);
                return rule;
            });
    }

    ASSERT_EQ(m_networkService.applyConfig(configFile), EXIT_SUCCESS);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
