//
// Created by linyxus on 17-10-2.
//

#include "../../include/misc/random.h"

namespace dnet
{
    namespace misc
    {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution;
        auto dice = std::bind(distribution, generator);

        unsigned int rand_int(unsigned int max)
        {
            return (unsigned int)(dice() * max);
        }
    }
}