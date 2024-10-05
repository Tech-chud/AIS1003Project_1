#ifndef RANDOMGEN_HPP
#define RANDOMGEN_HPP

#include <random>

namespace RandomGen {

    // Random float generator in a given range
    inline float randomFloat(float min, float max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    // Random integer generator in a given range
    inline int randomInt(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

} // namespace RandomGen

#endif // RANDOMGEN_HPP
