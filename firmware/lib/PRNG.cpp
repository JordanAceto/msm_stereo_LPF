#include "PRNG.hpp"

namespace PRNG
{
    static const uint32_t SEED = 987654321u;

    static uint32_t z1 = SEED;
    static uint32_t z2 = SEED;
    static uint32_t z3 = SEED;
    static uint32_t z4 = SEED;

    uint32_t nextRand(void)
    {
        uint32_t b;

        b = ((z1 << 6u) ^ z1) >> 13u;
        z1 = ((z1 & 4294967294u) << 18u) ^ b;
        b = ((z2 << 2u) ^ z2) >> 27u;
        z2 = ((z2 & 4294967288u) << 2u) ^ b;
        b = ((z3 << 13) ^ z3) >> 21u;
        z3 = ((z3 & 4294967280u) << 7u) ^ b;
        b = ((z4 << 3u) ^ z4) >> 12u;
        z4 = ((z4 & 4294967168u) << 13u) ^ b;

        return (z1 ^ z2 ^ z3 ^ z4);
    }
}
