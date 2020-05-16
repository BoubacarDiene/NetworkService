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

using ::testing::_;
using ::testing::AtLeast;

using namespace service::plugins::logger;
using namespace service::plugins::config;
using namespace utils::file;

namespace {

class JsonConfigTestFixture : public ::testing::Test {

protected:
    JsonConfigTestFixture() : m_jsonConfig(m_mockLogger, m_mockReader)
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));
    }

    MockReader m_mockReader;
    MockLogger m_mockLogger;
    Config m_jsonConfig;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(JsonConfigTestFixture, shouldRaiseAnExceptionIfConfigIsInvalid)
{
    const std::string configFile("/dev/null");

    EXPECT_CALL(m_mockReader, readFromStream(_, _))
        .WillOnce([]([[maybe_unused]] std::istream& stream, std::string& result) {
            const std::string configFileContent("{}");
            result.assign(configFileContent);
        });

    try {
        // The goal is to use this project only with valid configs.
        // Raising an exception indirectly allows to validate the
        // json config
        auto data = m_jsonConfig.load(configFile);
        FAIL() << "Should fail because the config is invalid";
    }
    catch (const std::exception& e) {
        // Expected!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(JsonConfigTestFixture, shouldReturnExpectedConfigDataIfConfigIsValid)
{
    const std::string configFile("/dev/null");

    EXPECT_CALL(m_mockReader, readFromStream(_, _))
        .WillOnce([]([[maybe_unused]] std::istream& stream, std::string& result) {
            const char* configFileContent
                = "{"
                  "    \"network\": {"
                  "        \"interfaceNames\": [\"lo\"],"

                  "        \"interfaceCommands\": ["
                  "            \"/sbin/ip tuntap add tap10 mode tap\""
                  "        ],"

                  "        \"layerCommands\": ["
                  "            {"
                  "                \"pathname\": \"/proc/sys/net/ipv4/ip_forward\","
                  "                \"value\": \"0\""
                  "            }"
                  "        ]"
                  "    },"

                  "    \"rules\": ["
                  "        {"
                  "            \"name\": \"rule 1.1\","
                  "            \"commands\": ["
                  "                \"/sbin/iptables -P OUTPUT ACCEPT\","
                  "                \"/sbin/iptables -P INPUT DROP\""
                  "            ]"
                  "        }"
                  "    ]"
                  "}";
            result.assign(configFileContent);
        });

    auto configData = m_jsonConfig.load(configFile);

    ASSERT_NE(configData, nullptr);

    ASSERT_EQ(configData->network.interfaceNames.size(), 1);
    ASSERT_EQ(configData->network.interfaceNames[0], "lo");

    ASSERT_EQ(configData->network.interfaceCommands.size(), 1);
    ASSERT_EQ(configData->network.interfaceCommands[0],
              "/sbin/ip tuntap add tap10 mode tap");

    ASSERT_EQ(configData->network.layerCommands.size(), 1);
    ASSERT_EQ(configData->network.layerCommands[0].pathname,
              "/proc/sys/net/ipv4/ip_forward");
    ASSERT_EQ(configData->network.layerCommands[0].value, "0");

    ASSERT_EQ(configData->rules.size(), 1);
    ASSERT_EQ(configData->rules[0].name, "rule 1.1");
    ASSERT_EQ(configData->rules[0].commands.size(), 2);
    ASSERT_EQ(configData->rules[0].commands[0], "/sbin/iptables -P OUTPUT ACCEPT");
    ASSERT_EQ(configData->rules[0].commands[1], "/sbin/iptables -P INPUT DROP");
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
