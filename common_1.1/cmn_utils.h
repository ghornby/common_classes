/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/



#ifndef CMN_MISC_UTILS_HEADER_FILE
#define CMN_MISC_UTILS_HEADER_FILE

#include <iostream>
#include <stdexcept>
#include <string>

namespace CmnClass {

void get_time(long &sec, long &usec);
void get_time_difference(long sec1, long usec1, long sec2, long usec2,
			 long& d_sec, long& d_usec);


void print_datetime(std::ostream& ostr);

void print_time();
void print_time(std::ostream& ostr);

bool is_pair1_greater_ii( const std::pair<int, int>& i, const std::pair<int, int>& j );
bool is_pair1_smaller_ii( const std::pair<int, int>& i, const std::pair<int, int>& j );
bool is_pair1_greater_id( const std::pair<int, double>& i, const std::pair<int, double>& j );
bool is_pair1_smaller_id( const std::pair<int, double>& i, const std::pair<int, double>& j );

bool is_pair1_greater_sd( const std::pair<std::string, double>& i,
			  const std::pair<std::string, double>& j );
bool is_pair1_smaller_sd( const std::pair<std::string, double>& i,
			  const std::pair<std::string, double>& j );

bool increase_stack_size();
bool increase_stack_size(unsigned long num_meg);



class CmnException : public std::exception {
public:
  CmnException(const char* msg = 0);
  CmnException(const std::string& msg = "");
  ~CmnException() throw() {};

  const char* what();

private:
  const std::string data_;
};

}

#endif
