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

#include <cstring>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "utils/helper/Errno.h"

using ::testing::HasSubstr;

using namespace utils::helper;

namespace {

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST(ErrnoTestSuite, returnStrerrorForEmptyFunctionName)
{
    EXPECT_EQ(Errno::toString("", EACCES), std::strerror(EACCES));
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST(ErrnoTestSuite, workEvenForInvalidErrorCode)
{
    const std::string result = Errno::toString("NAME", -1);

    EXPECT_THAT(result, HasSubstr(std::string("NAME")));
    EXPECT_THAT(result, HasSubstr(std::strerror(-1)));
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST(ErrnoTestSuite, concatenateStrerrorAndFunctionName)
{
    const std::array errnoValues = {EACCES, EAGAIN, EBUSY};
    std::string result;

    for (const auto& errnoValue : errnoValues) {
        result = Errno::toString("NAME", errnoValue);

        EXPECT_THAT(result, HasSubstr(std::string("NAME")));
        EXPECT_THAT(result, HasSubstr(std::strerror(errnoValue)));
    }
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
