//
// Created by linyxus on 17-9-16.
//

#include "../../include/misc/exception.h"

namespace dnet
{
    namespace misc
    {
        exception make_error(const std::string &module_name, const std::string &info)
        {
            exception ret;
            ret.module_name = module_name;
            ret.info = info;
            return ret;
        }

        std::ostream &operator<<(std::ostream &out, const exception &e)
        {
            out << "--------------------" << std::endl;
            out << "[Error] From module " << e.module_name << std::endl;
            out << e.info << std::endl;
            out << "--------------------" << std::endl;
            return out;
        }
    }
}
