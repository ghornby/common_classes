/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/


#ifndef CMN_RANDOM_MT_HEADER_FILE
#define CMN_RANDOM_MT_HEADER_FILE

#include <vector>


namespace CmnClass {

void init_genrand(unsigned long s);
unsigned long genrand_int32(void);
double genrand_double1(void);
double genrand_double2(void);

bool is_random_seed_set();
unsigned long get_random_seed();
void seed_random(unsigned long seed);
unsigned int random_int(int max);
unsigned int random_integer();
double random_double();
double random_norm();

void shuffle(std::vector<double>& vec);
void shuffle(std::vector<int>& vec);
void shuffle(std::vector<unsigned int>& vec);

}

#endif
