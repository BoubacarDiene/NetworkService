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

#include <sstream>

#include "gtest/gtest.h"

#include "mocks/MockLogger.h"
#include "utils/file/writer/Writer.h"

using ::testing::AtLeast;

using namespace service::plugins::logger;
using namespace utils::file;

namespace {

class WriterTestFixture : public ::testing::Test {

protected:
    WriterTestFixture() : m_writer(m_mockLogger)
    {
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));
    }

    Writer m_writer;

private:
    MockLogger m_mockLogger;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(WriterTestFixture, raiseExceptionIfInvalidStream)
{
    try {
        std::ostringstream stream;
        stream.setstate(std::ios::failbit);

        m_writer.writeToStream(stream, "0");
        FAIL() << "Should fail because the stream is not valid";
    }
    catch (const std::runtime_error& e) {
        // Expected!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(WriterTestFixture, replaceContentIfValidStream)
{
    // Use ostringstream because it does not require interaction
    // with the filesystem
    std::ostringstream stream;
    m_writer.writeToStream(stream, "value");

    // Check content
    ASSERT_EQ(stream.str(), "value");
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
