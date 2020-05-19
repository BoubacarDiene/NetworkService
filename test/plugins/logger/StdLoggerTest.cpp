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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "plugins/logger/Logger.h"

using ::testing::HasSubstr;

using namespace service::plugins::logger;

namespace {

class StdLoggerTestFixture : public ::testing::Test {

protected:
    Logger m_logger;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(StdLoggerTestFixture, debugLogShouldContainProvidedMessage)
{
    std::string message = "A test to print debug message";

    // Set the buffer to stream to and save the original bufferr
    std::ostringstream buffer;
    std::streambuf* previousBuffer = std::cout.rdbuf(buffer.rdbuf());

    // Write the message then check result
    m_logger.debug(message);
    EXPECT_THAT(buffer.str(), HasSubstr(message));

    // Restore the original buffer
    std::cout.rdbuf(previousBuffer);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(StdLoggerTestFixture, infoLogShouldContainProvidedMessage)
{
    std::string message = "A test to print info message";

    // Set the buffer to stream to and save the original bufferr
    std::ostringstream buffer;
    std::streambuf* previousBuffer = std::cout.rdbuf(buffer.rdbuf());

    // Write the message then check result
    m_logger.info(message);
    EXPECT_THAT(buffer.str(), HasSubstr(message));

    // Restore the original buffer
    std::cout.rdbuf(previousBuffer);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(StdLoggerTestFixture, warnLogShouldContainProvidedMessage)
{
    std::string message = "A test to print warn message";

    // Set the buffer to stream to and save the original bufferr
    std::ostringstream buffer;
    std::streambuf* previousBuffer = std::cout.rdbuf(buffer.rdbuf());

    // Write the message then check result
    m_logger.warn(message);
    EXPECT_THAT(buffer.str(), HasSubstr(message));

    // Restore the original buffer
    std::cout.rdbuf(previousBuffer);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(StdLoggerTestFixture, errorLogShouldContainProvidedMessage)
{
    std::string message = "A test to print error message";

    // Set the buffer to stream to and save the original bufferr
    std::ostringstream buffer;
    std::streambuf* previousBuffer = std::cerr.rdbuf(buffer.rdbuf());

    // Write the message then check result
    m_logger.error(message);
    EXPECT_THAT(buffer.str(), HasSubstr(message));

    // Restore the original buffer
    std::cerr.rdbuf(previousBuffer);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
