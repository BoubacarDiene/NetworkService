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

#include "mocks/MockWriter.h"

#include "plugins/network/layer/Layer.h"

using ::testing::_;

using namespace service::plugins::network::layer;
using namespace utils::file;

namespace {

class LayerTestFixture : public ::testing::Test {

protected:
    LayerTestFixture() : m_layer(m_mockWriter) {}

    MockWriter m_mockWriter;
    Layer m_layer;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LayerTestFixture, shouldCallWriterWithExpectedValues)
{
    const std::string pathname("/dev/null");
    const std::string expectedValue("value");

    EXPECT_CALL(m_mockWriter, writeToStream(_, _))
        .WillOnce([&expectedValue]([[maybe_unused]] std::ostream& stream,
                                   const std::string& value) {
            ASSERT_EQ(value, expectedValue);
        });

    m_layer.applyCommand(pathname, expectedValue);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
