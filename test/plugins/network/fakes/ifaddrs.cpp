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

#include "ifaddrs.h"

namespace {

enum Test gTest = SUCCESS;

struct sockaddr gIfaAddr;
struct ifaddrs gAddrsNext;
struct ifaddrs gAddrsFirst = {&gAddrsNext, nullptr, nullptr};

char gInterface[] = "fakeInterface";

}

/*
 * This fake version of ifaddrs allows to test all lines in hasInterface() method:
 * 1- Return -1 to make hasInterface() throw an exception
 * 2- Set the first ifa_addr to NULL to make hasInterface() continue browsing the
 *    returned list
 * 3- Return a data structure for which "fakeInterface" is considered as a valid
 *    network interface
 */
int getifaddrs(struct ifaddrs** __ifap)
{
    if (gTest == FAILURE) {
        return -1;
    }

    gAddrsFirst.ifa_next->ifa_name            = static_cast<char*>(gInterface);
    gAddrsFirst.ifa_next->ifa_addr            = &gIfaAddr;
    gAddrsFirst.ifa_next->ifa_addr->sa_family = AF_PACKET;

    *__ifap = &gAddrsFirst;

    return 0;
}

void freeifaddrs([[maybe_unused]] struct ifaddrs* __ifa) {}

void setIfaddrsTest(enum Test test)
{
    gTest = test;
}
