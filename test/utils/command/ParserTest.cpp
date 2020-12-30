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

#include "utils/command/parser/Parser.h"

using namespace utils::command;

namespace {

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST(ParserTest, returnTheSameStringIfInvalidDelimiter)
{
    const std::string command("/sbin/iptables -P OUTPUT ACCEPT");
    auto result = Parser::parse(command, ';');

    ASSERT_STREQ(result->pathname, command.c_str());
    ASSERT_EQ(result->argc, 1);
    ASSERT_STREQ(result->argv[0], command.c_str());
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST(ParserTest, returnSplittedStringIfValidDelimiter)
{
    const std::string command("/sbin/iptables -P OUTPUT ACCEPT");
    auto result = Parser::parse(command);

    ASSERT_STREQ(result->pathname, "/sbin/iptables");
    ASSERT_EQ(result->argc, 4);
    ASSERT_STREQ(result->argv[0], "/sbin/iptables");
    ASSERT_STREQ(result->argv[1], "-P");
    ASSERT_STREQ(result->argv[2], "OUTPUT");
    ASSERT_STREQ(result->argv[3], "ACCEPT");
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
