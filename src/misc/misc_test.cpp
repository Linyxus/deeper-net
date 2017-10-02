//
// Created by linyxus on 17-10-2.
//

#include "../../include/misc/random.h"
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

    TEST(random, rand_int)
    {
        std::cout << dnet::misc::rand_int(1000) << std::endl;
    }
}