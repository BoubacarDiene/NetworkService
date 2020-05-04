//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//                                                                          //
//  Copyright © 2020 Boubacar DIENE                                         //
//                                                                          //
//  This file is part of NetworkService project.                            //
//                                                                          //
//  NetworkService is free software: you can redistribute it and/or modify  //
//  it under the terms of the GNU General Public License as published by    //
//  the Free Software Foundation, either version 2 of the License, or       //
//  (at your option) any later version.                                     //
//                                                                          //
//  NetworkService is distributed in the hope that it will be useful,       //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//  GNU General Public License for more details.                            //
//                                                                          //
//  You should have received a copy of the GNU General Public License       //
//  along with NetworkService. If not, see <http://www.gnu.org/licenses/>   //
//  or write to the Free Software Foundation, Inc., 51 Franklin Street,     //
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           //
//                                                                          //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

#ifndef __UTILS_COMMAND_EXECUTOR_H__
#define __UTILS_COMMAND_EXECUTOR_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace utils::command {

class Executor {

public:
    enum Flags : unsigned int {
        WAIT_COMMAND    = (1u << 0u),
        RESEED_PRNG     = (1u << 1u),
        SANITIZE_FILES  = (1u << 2u),
        DROP_PRIVILEGES = (1u << 3u),
        ALL = (WAIT_COMMAND | RESEED_PRNG | SANITIZE_FILES | DROP_PRIVILEGES)
    };

    explicit Executor(const service::plugins::logger::ILogger& logger);

    ~Executor();

    Executor(const Executor&) = delete;

    Executor& operator=(const Executor&) = delete;

    Executor(Executor&&) = delete;

    Executor& operator=(Executor&&) = delete;

    void exec(const char* pathname,
              char* const argv[],
              char* const envp[],
              Flags flags = Flags::ALL) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
