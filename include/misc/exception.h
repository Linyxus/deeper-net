//
// Created by linyxus on 17-9-16.
//

#ifndef DEEPER_NET_EXCEPTION_H
#define DEEPER_NET_EXCEPTION_H

#include <string>
#include <iostream>

namespace dnet
{
    namespace misc
    {
        struct exception;
        exception make_error(const std::string &module_name, const std::string &info);
        std::ostream &operator<<(std::ostream &out, const exception &e);

        struct exception
        {
            std::string module_name;
            std::string info;
        };
    }
}

#endif //DEEPER_NET_EXCEPTION_H
