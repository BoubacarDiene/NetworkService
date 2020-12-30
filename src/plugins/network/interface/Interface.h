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

#ifndef __PLUGINS_NETWORK_INTERFACE_INTERFACE_H__
#define __PLUGINS_NETWORK_INTERFACE_INTERFACE_H__

#include <memory>
#include <string>

#include "utils/command/executor/IExecutor.h"

namespace service::plugins::network::interface {

/**
 * @class Interface Interface.h "plugins/network/interface/Interface.h"
 * @ingroup Implementation
 *
 * @brief Helper class to handle "interface commands"
 *
 * @note Copy contructor, copy-assignment operator, move constructor and
 *       move-assignment operator are defined to be compliant with the
 *       "Rule of five"
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
class Interface {

public:
    /**
     * Class constructor
     *
     * @param executor Command executor to use
     */
    explicit Interface(const utils::command::IExecutor& executor);

    /** Class destructor */
    ~Interface();

    /** Class copy constructor */
    Interface(const Interface&) = delete;

    /** Class copy-assignment operator */
    Interface& operator=(const Interface&) = delete;

    /** Class move constructor */
    Interface(Interface&&) = delete;

    /** Class move-assignment operator */
    Interface& operator=(Interface&&) = delete;

    /** Apply the requested "interface command" */
    void applyCommand(const std::string& command) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
