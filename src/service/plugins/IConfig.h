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

#ifndef __SERVICE_PLUGINS_ICONFIG_H__
#define __SERVICE_PLUGINS_ICONFIG_H__

#include <memory>

#include "IConfigData.h"

namespace service::plugins::config {

/**
 * @interface IConfig IConfig.h "service/plugins/IConfig.h"
 * @ingroup Abstraction
 *
 * @brief Load the configuration used by the service to set up the network
 *
 * This class is the high level interface that must be implemented by config
 * plugin. The core service depends on it and not on its implementation(s) to
 * respect the Dependency Inversion Principle. It is possible to retrieve the
 * network configuration in various means that just need to be implemented if
 * required:
 *
 * - From a JSON file (.json)
 * - From a YAML file (.yaml)
 * - From a XML file (.xml)
 * - From a Text file (.txt)
 * - From a database (sqlite, ...)
 * - etc.
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
class IConfig {

public:
    /** Class constructor */
    IConfig() = default;

    /** Class destructor made virtual because it is used as base class by
     *  derived classes in config plugin */
    virtual ~IConfig() = default;

    /** Class copy constructor */
    IConfig(const IConfig&) = delete;

    /** Class copy-assignment operator */
    IConfig& operator=(const IConfig&) = delete;

    /** Class move constructor */
    IConfig(IConfig&&) = delete;

    /** Class move-assignment operator */
    IConfig& operator=(IConfig&&) = delete;

    /**
     * @brief Load the the provided configuration file into memory
     *
     * @param configFile Configuration file to load
     *
     * @return A data structure containing all the informations retrieved
     *         from the configuration file
     *
     * @see ConfigData
     */
    [[nodiscard]] virtual std::unique_ptr<ConfigData>
        load(const std::string& configFile) const = 0;
};

}

#endif
