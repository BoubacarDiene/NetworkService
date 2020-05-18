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

/**
 * @file plugins/network/Wrapper.h
 * @ingroup Implementation
 *
 * @brief This is a wrapper to "low level calls" used in Network.cpp. Putting them
 *        in a separate file makes it a bit more easy to test hasInterface() method.
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date May 2020
 */

#ifndef __PLUGINS_NETWORK_WRAPPER_H__
#define __PLUGINS_NETWORK_WRAPPER_H__

#include <ifaddrs.h>
#include <sys/types.h>

/**
 * @fn int osGetifaddrs(struct ifaddrs** ifap)
 *
 * @brief A wrapper to getifaddrs()
 *
 * It creates a linked list of structures describing the network interfaces of
 * the local system.
 *
 * @param ifap The address of the first item of the list is stored in *ifap
 *
 * @return On success, 0 is returned. On error, -1 is returned and errno is set
 *         appropriately
 */
int osGetifaddrs(struct ifaddrs** ifap);

/**
 * @fn void osFreeifaddrs(struct ifaddrs* ifa)
 *
 * @brief A wrapper to freeifaddrs()
 *
 * It is used to free resources allocated by @ref osGetifaddrs
 *
 * @param ifa The resource to free
 *
 * @return On success, 0 is returned. On error, -1 is returned and errno is set
 *         appropriately
 */
void osFreeifaddrs(struct ifaddrs* ifa);

#endif
