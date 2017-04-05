/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/


#ifndef CMN_STRING_PROC_HEADER_FILE
#define CMN_STRING_PROC_HEADER_FILE

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace CmnClass {

extern const int Max_Line_Length;


int next_field(const char *line);
int read_integer(const char *line);
double read_double(const char *line);

int read_integer(std::istream& line);
double read_double(std::istream& line);


std::istream& read_vec(std::istream& istr, std::vector<bool>& vec, std::string name);
std::istream& read_vec(std::istream& istr, std::vector<int>& vec, std::string name);
std::istream& read_vec(std::istream& istr, std::vector<unsigned>& vec, std::string name);
std::istream& read_vec(std::istream& istr, std::vector<double>& vec, std::string name);
std::istream& read_vec(std::istream& istr, std::vector<std::string>& vec, std::string name);

std::ostream& write_vec(std::ostream& ostr, const std::vector<bool>& vec);
std::ostream& write_vec(std::ostream& ostr, const std::vector<int>& vec);
std::ostream& write_vec(std::ostream& ostr, const std::vector<unsigned>& vec);
std::ostream& write_vec(std::ostream& ostr, const std::vector<double>& vec);
std::ostream& write_vec(std::ostream& ostr, const std::vector<std::string>& vec);

template <class T>
std::ostream& write_set(std::ostream& ostr, const std::set<T>& s);


std::ostream& write_set(std::ostream& ostr, const std::set<std::string>& s);
std::istream& read_set(std::istream& istr, std::set<std::string>& data, std::string name);


std::ostream& write_map(std::ostream& istr, const std::map<std::string,int>& m);


bool get_int(const char *string, int *val);
bool get_double(const char *string, double *val);
int find_field(const char *string);


std::string int_2_str(int val);


template <class T>
T from_string(const std::string& s)
{
  std::istringstream iss(s);
  T val;
  iss >> std::dec >> val;
  return val;
}



template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}


template <class T>
bool from_string(T& t, 
                 const std::string& s)
{
  std::istringstream iss(s);
  return !(iss >> std::dec >> t).fail();
}


std::istream& skip_comment_lines(std::istream& istr);


std::vector<std::string> &split(const std::string &s, char delim,
				std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);



}

#endif
