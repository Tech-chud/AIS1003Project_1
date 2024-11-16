//Used help from discussion in two stack overflow threads
//https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
//https://stackoverflow.com/questions/7560114/random-number-c-in-some-range


#ifndef RANDOMGEN_HPP
#define RANDOMGEN_HPP

namespace RandomGen {

    // Random float generator in a given range
    float randomFloat(float min, float max);

    // Random integer generator in a given range
    int randomInt(int min, int max);

}

#endif // RANDOMGEN_HPP

