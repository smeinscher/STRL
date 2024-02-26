//
// Created by SterlingMeinscher on 2/19/2024.
//

#ifndef STRLRANDOM_H
#define STRLRANDOM_H

#include <random>

namespace strl
{

typedef std::mt19937 rng_type;

class STRLRandom
{
public:
	static void seed(unsigned int);
	// TODO: try to do random better
	static int get_random_int(int lower_bound, int upper_bound);
	static float get_random_float(float lower_bound, float upper_bound);

private:
	static rng_type rng_;
};

} // strl

#endif //STRLRANDOM_H
