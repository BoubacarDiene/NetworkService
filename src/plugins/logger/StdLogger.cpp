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

#include <iostream>

#include "Logger.h"

#define BLUE   "\033[0;34m"
#define YELLOW "\033[1;33m"
#define RED    "\033[5;31m"
#define GREEN  "\033[0;32m"

#define END "\033[0m"

using namespace service::plugins::logger;

struct Logger::Internal {
    static inline void debug(const std::string& message,
                             const char* const color = BLUE)
    {
        std::cout << color << message << END << std::endl;
    }

    static inline void error(const std::string& message,
                             const char* const color = RED)
    {
        std::cerr << color << message << END << std::endl;
    }
};

Logger::Logger() : m_internal(std::make_unique<Internal>()) {}

Logger::~Logger() = default;

void Logger::debug([[maybe_unused]] const std::string& message) const
{
#ifndef NDEBUG
    Internal::debug(message);
#endif
}

void Logger::info(const std::string& message) const
{
    Internal::debug(message, GREEN);
}

void Logger::warn(const std::string& message) const
{
    Internal::debug(message, YELLOW);
}

void Logger::error(const std::string& message) const
{
    Internal::error(message);
}
