//
// Created by SterlingMeinscher on 2/19/2024.
//

#include <ctime>
#include "STRLRandom.h"

namespace strl
{

rng_type STRLRandom::rng_{};

void STRLRandom::seed(unsigned int seed)
{
	rng_.seed(seed);
}

int STRLRandom::get_random_int(int lower_bound, int upper_bound)
{
	std::uniform_int_distribution<int> udist(lower_bound, upper_bound);
	int random_number = udist(rng_);
	return random_number;
}

float STRLRandom::get_random_float(float lower_bound, float upper_bound)
{
	std::uniform_real_distribution<float> udist(lower_bound, upper_bound);
	float random_number = udist(rng_);
	return random_number;
}

} // strl