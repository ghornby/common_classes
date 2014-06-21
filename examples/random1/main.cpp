#include "cmn_random.h"
#include "cmn_string_proc.h"
#include "cmn_utils.h"


#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char **argv)
{
  cout << "hello world" << endl;


  CmnClass::seed_random(0);

  double val = CmnClass::random_double();
  cout << "Random number: " << val << endl;

  return 0;
}
