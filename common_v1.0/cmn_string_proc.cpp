/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/



#include "cmn_string_proc.h"

#include <cstdlib>
#include <cstdio>
using namespace std;



namespace CmnClass {

const int Max_Line_Length = 255; // max line allowed in configuration file.

int next_field(const char *line)
{
  int i = 0;

  while ((line[i] != ' ') && (line[i] != ':') &&
	 (line[i] != ',') && (line[i] != 0)) {
    i++;
  }

  if (line[i] != 0)
    return i+1;
  return i;
}


int read_integer(const char *line)
{
  int i = 0;
  int val;

  char tmp[255];
  while ((line[i] != ' ') && (line[i] != ',')
	 && (line[i] != ')') && (line[i] != '>') &&
	 (line[i] != 0)) {
    tmp[i] = line[i];
    if (++i>254) {
      // Should throw an error or something.
      cout << "alps_util :: read_integer() error reading line: " << line << endl;
      while (1) ;
    }
  }

  tmp[i] = 0;
  val = atoi(tmp);

  return val;
}


int read_integer(istream& istr)
{
  stringstream num_ss;

  char ch = istr.get();
  if (ch == '-') {
    // Handle special case of leading '-' for negative numbers:
    num_ss << ch;
    ch = istr.get();
  }

  while ((ch >= '0') && (ch <= '9')) {
    // The next character is part of the number, so add to num_ss stringstream:
    num_ss << ch;
    ch = istr.get();
  }
  istr.unget();


#ifdef OLD
  char next_ch;
  next_ch = istr.peek();

  while ((next_ch != ' ') && (next_ch != ',')
	 && (next_ch != ')') && (next_ch != '>') &&
	 (next_ch != 0)) {
    // The next character is part of the number, so add to num_ss stringstream:
    char ch;
    line >> ch;
    num_ss << ch;

    // Look at the next character:
    next_ch = line.peek();
  }
#endif

  int val;
  num_ss >> val;

  return val;
}



double read_double(istream& istr)
{
  stringstream num_ss;

  char next_ch;
  next_ch = istr.peek();

  while ((next_ch != ' ') && (next_ch != ',') && (next_ch != ':')
	 && (next_ch != ')') && (next_ch != '>') &&
	 (next_ch != 0)) {
    // The next character is part of the number, so add to num_ss stringstream:
    char ch = istr.get();
    num_ss << ch;

    // Look at the next character:
    next_ch = istr.peek();
  }

  double val;
  num_ss >> val;
  return val;
}



double read_double(const char *line)
{
  double val;

  if ((line[0] != '-') &&
      ((line[0] < '0') || (line[0] > '9'))) {
    // not a number.
    printf("read_double() - error reading value at: %s.\n", line);
    return -9999.9;
  }

  int i = 0;
  char tmp[255];
  while ((line[i] != ' ') && (line[i] != ':') &&
	 (line[i] != 0)) {
    i++;
    tmp[i] = line[i];
    if (i>254) {
      // Should throw an error or something.
      cout << "alps_util :: read_double() error reading line: " << line << endl;
      while (1) ;
    }
  }

  tmp[i] = 0;
  val = atof(tmp);

  return val;
}


bool get_int(const char *string, int *val)
{
  int i;

  i = find_field(string);
  *val = atoi(string+i);
  return true;
}


bool get_double(const char *string, double *val)
{
  int i;

  i = find_field(string);
  *val = atof(string+i);
  return true;
}



// Returns location of input field, 0 if not found.
int find_field(const char *string)
{
  int i=0;
  // Find separator: ':'.
  while (string[i] != ':') {
    i++;
    if (i > Max_Line_Length) {
      printf("Pop :: parsing configuration file - error finding separator<%s>.\n", string);
      return 0;
    }
  }
  i++;

  // Move to end of whitespace.
  while (string[i] == ' ') {
    i++;
    if (i >= Max_Line_Length) {
      printf("Pop :: parsing configuration file - error finding field.\n");
      return 0;
    }
  }

  return i;
}


// This function will move ahead lines in istr until
// it comes to one which does not start with a '!' or a '#'.
istream& skip_comment_lines(istream& istr)
{
  string line;
  char token = istr.peek();

  while ((token == '!') || (token == '#') || (token == 10) || (token == 13)) {
    // This line is a comment line since it starts with ! or #,
    // read it and move on to the next.
    getline(istr, line);
    token = istr.peek();
  }
  return istr;
}



std::vector<std::string> &split(const std::string &s, char delim,
				std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    elems.clear();
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}


std::string int_2_str(int val)
{
  std::stringstream ss;
  ss << val;
  return ss.str();
}


istream& read_vec(istream& istr, vector<bool>& vec, string name)
{
  string line;
  vector<string> words;
  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != 1) {
    stringstream msg;
    msg << name << " :: read_vec() - error reading number of vals:" << line << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }
  unsigned int num = from_string<int>(words[0]);

  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != num) {
    stringstream msg;
    msg << name << "  :: read_vec() - error, number of vals " << num << ", does not match line: "
	<< words.size() << ": " << line << endl;
    cout << msg;
    while (1) ;
    throw runtime_error(msg.str());
  }

  vec.clear();
  for (vector<bool>::size_type i=0; i<words.size(); i++) {
    int val = from_string<bool>(words[i]);
    vec.push_back(val);
  }

  return istr;
}


istream& read_vec(istream& istr, vector<int>& vec, string name)
{
  string line;
  vector<string> words;
  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != 1) {
    stringstream msg;
    msg << name << " :: read_vec() - error reading number of vals:" << line << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }
  unsigned int num = from_string<int>(words[0]);

  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != num) {
    stringstream msg;
    msg << name << "  :: read_vec() - error, number of vals " << num << ", does not match line: "
	<< words.size() << ": " << line << endl;
    cout << msg;
    while (1) ;
    throw runtime_error(msg.str());
  }

  vec.clear();
  for (vector<int>::size_type i=0; i<words.size(); i++) {
    int val = from_string<int>(words[i]);
    vec.push_back(val);
  }

  return istr;
}


istream& read_vec(istream& istr, vector<unsigned>& vec, string name)
{
  string line;
  vector<string> words;
  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != 1) {
    stringstream msg;
    msg << name << " :: read_vec() - error reading number of vals:" << line << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }
  unsigned int num = from_string<int>(words[0]);

  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != num) {
    stringstream msg;
    msg << name << "  :: read_vec() - error, number of vals " << num << ", does not match line: "
	<< words.size() << ": " << line << endl;
    cout << msg;
    while (1) ;
    throw runtime_error(msg.str());
  }

  vec.clear();
  for (vector<int>::size_type i=0; i<words.size(); i++) {
    unsigned val = from_string<unsigned>(words[i]);
    vec.push_back(val);
  }

  return istr;
}



istream& read_vec(istream& istr, vector<double>& vec, string name)
{
  string line;
  vector<string> words;
  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != 1) {
    stringstream msg;
    msg << name << " :: read_vec() - error reading number of vals:" << line << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }
  unsigned int num = from_string<int>(words[0]);

  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != num) {
    stringstream msg;
    msg << name << "  :: read_vec() - error, number of vals " << num << ", does not match line: "
	<< words.size() << ": " << line << endl;
    cout << msg;
    while (1) ;
    throw runtime_error(msg.str());
  }

  vec.clear();
  for (vector<int>::size_type i=0; i<words.size(); i++) {
    double val = from_string<double>(words[i]);
    vec.push_back(val);
  }

  return istr;
}



istream& read_vec(istream& istr, vector<string>& vec, string name)
{
  string line;
  vector<string> words;
  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != 1) {
    stringstream msg;
    msg << name << " :: read_vec() - error reading number of vals:" << line << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }
  unsigned int num = from_string<int>(words[0]);

  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != num) {
    stringstream msg;
    msg << name << "  :: read_vec() - error, number of vals " << num << ", does not match line: "
	<< words.size() << ": " << line << endl;
    cout << msg;
    while (1) ;
    throw runtime_error(msg.str());
  }

  vec.clear();
  for (vector<int>::size_type i=0; i<words.size(); i++) {
    string val = from_string<string>(words[i]);
    vec.push_back(val);
  }

  return istr;
}



ostream& write_vec(ostream& ostr, const vector<bool>& vec)
{
  ostr << vec.size() << endl;
  for (vector<bool>::size_type i=0; i<vec.size(); i++) {
    ostr << vec[i];
    if (i+1 < vec.size()) {
      ostr << " ";
    }
  }
  if (vec.size() > 0) {
    ostr << endl;
  }

  return ostr;
}


ostream& write_vec(ostream& ostr, const vector<int>& vec)
{
  ostr << vec.size() << endl;
  for (vector<int>::size_type i=0; i<vec.size(); i++) {
    ostr << vec[i];
    if (i+1 < vec.size()) {
      ostr << " ";
    }
  }
  if (vec.size() > 0) {
    ostr << endl;
  }

  return ostr;
}


ostream& write_vec(ostream& ostr, const vector<unsigned>& vec)
{
  ostr << vec.size() << endl;
  for (vector<unsigned>::size_type i=0; i<vec.size(); i++) {
    ostr << vec[i];
    if (i+1 < vec.size()) {
      ostr << " ";
    }
  }
  if (vec.size() > 0) {
    ostr << endl;
  }

  return ostr;
}



ostream& write_vec(ostream& ostr, const vector<double>& vec)
{
  ostr << vec.size() << endl;
  for (vector<double>::size_type i=0; i<vec.size(); i++) {
    ostr << vec[i];
    if (i+1 < vec.size()) {
      ostr << " ";
    }
  }
  if (vec.size() > 0) {
    ostr << endl;
  }

  return ostr;
}


// Assumes that each string in the vector does not have any whitespace.
ostream& write_vec(ostream& ostr, const vector<string>& vec)
{
  ostr << vec.size() << endl;
  for (vector<string>::size_type i=0; i<vec.size(); i++) {
    ostr << vec[i];
    if (i+1 < vec.size()) {
      ostr << " ";
    }
  }
  if (vec.size() > 0) {
    ostr << endl;
  }

  return ostr;
}


template <class T>
ostream& write_set(ostream& ostr, const set<T>& s)
{
  ostr << s.size() << endl;

  unsigned int ctr = 0;
  typename set<T>::const_iterator it=s.begin();
  for (; it!=s.end(); ++it) {
    ostr << *it;
    if (++ctr < s.size()) {
      ostr << " ";
    }
  }
  if (s.size() > 0) {
    ostr << endl;
  }

  return ostr;
}



ostream& write_set(ostream& ostr, const set<string>& s)
{
  ostr << s.size() << endl;

  unsigned int ctr = 0;
  set<string>::const_iterator it=s.begin();
  for (; it!=s.end(); ++it) {
    ostr << *it;
    if (++ctr < s.size()) {
      ostr << " ";
    }
  }
  if (s.size() > 0) {
    ostr << endl;
  }

  return ostr;
}



istream& read_set(istream& istr, set<string>& data, string name)
{
  string line;
  vector<string> words;
  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != 1) {
    stringstream msg;
    msg << name << " :: read_set() - error reading number of vals:" << line << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }

  data.clear();
  unsigned int num = from_string<int>(words[0]);
  if (num == 0) {
    return istr;
  }

  getline(istr, line);
  split(line, ' ', words);
  if (words.size() != num) {
    stringstream msg;
    msg << name << "  :: read_vec() - error, number of vals " << num << ", does not match line: "
	<< words.size() << ": " << line << endl;
    cout << msg << endl;
    while (1) ;
    throw runtime_error(msg.str());
  }


  for (vector<int>::size_type i=0; i<words.size(); i++) {
    string val = from_string<string>(words[i]);
    data.insert(val);
  }

  return istr;
}






ostream& write_map(ostream& ostr, const map<string,int>& m)
{
  ostr << m.size() << endl;

  unsigned int ctr = 0;
  map<string,int>::const_iterator it=m.begin();
  for (; it!=m.end(); ++it) {
    ostr << "< " << (*it).first << " , " << (*it).second << " >";
    if (++ctr < m.size()) {
      ostr << " ";
    }
  }
  if (m.size() > 0) {
    ostr << endl;
  }

  return ostr;
}




} // namespace end





#ifdef EXAMPLES

{
// http://www.codeguru.com/forum/showthread.php?t=231054
  int i;
  float f;
  
  // the third parameter of from_string() should be 
  // one of std::hex, std::dec or std::oct
  if(from_string<int>(i, std::string("ff"), std::hex))
  {
    std::cout << i << std::endl;
  }
  else
  {
    std::cout << "from_string failed" << std::endl;
  }
  
  if(from_string<float>(f, std::string("123.456"), std::dec))
  {
    std::cout << f << std::endl;
  }
  else
  {
    std::cout << "from_string failed" << std::endl;
  }
}



{
  std::vector<std::string> x = split("one:two:three", ':');
}



#endif
