//
// Created by linyxus on 17-9-16.
//

#include "../../include/misc/exception.h"
#include "../../gtest/include/gtest/gtest.h"

namespace
{
    TEST(excption, throw_and_catch)
    {
        try {
            throw dnet::misc::make_error("TEST", "Whoops!");
        }
        catch (const dnet::misc::exception &e) {
            std::cout << e;
        }
    }
}