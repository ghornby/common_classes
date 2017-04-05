/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/



#include "cmn_utils.h"

#include <iostream>
#include <sys/resource.h>
#include <sys/time.h>
//include <time.h>
#include <sstream>
using namespace std;




namespace CmnClass {


void asctime(const struct tm *timeptr, stringstream& ss)
{
  static const char wday_name[][4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  static const char mon_name[][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  /*
  ss << timeptr->tm_min << timeptr->tm_sec
     << wday_name[timeptr->tm_wday]
     << mon_name[timeptr->tm_mon]
     << timeptr->tm_mday << timeptr->tm_hour
     << (1900 + timeptr->tm_year);
  */

  ss << (1900 + timeptr->tm_year)
     << " " << wday_name[timeptr->tm_wday]
     << " " << mon_name[timeptr->tm_mon];

  if (timeptr->tm_mday < 10) {
    ss << " ";
  }
  ss << " " << timeptr->tm_mday;

  if (timeptr->tm_hour < 10) {
    ss << " ";
  }
  ss << " " << timeptr->tm_hour;

  ss << ":";

  if (timeptr->tm_min < 10) {
    ss << "0";
  }
  ss << timeptr->tm_min << ":";


  if (timeptr->tm_sec < 10) {
    ss << "0";
  }
  ss << timeptr->tm_sec;
}


void print_datetime(ostream& ostr)
{
  time_t rawtime;
  struct tm * timeinfo;

  time( &rawtime );
  timeinfo = localtime( &rawtime );

  stringstream datetime;
  asctime(timeinfo, datetime);
  ostr << datetime.str();
}





void print_time(ostream& ostr)
{
  int sec, min, hour;
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);

  tp.tv_sec -= 7*3600; // change to PST.
  hour = (tp.tv_sec/3600) % 24;
  min = (tp.tv_sec/60) % 60;
  sec = tp.tv_sec % 60;

  ostr << hour << ":" << min << ":" << sec;
}


void get_time(long &sec, long &usec)
{
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);
  tp.tv_sec -= 7*3600; // change to PST.
  sec = tp.tv_sec;
  usec = tp.tv_usec;
}


void get_time_difference(long sec1, long usec1, long sec2, long usec2,
			 long& d_sec, long& d_usec)
{
  d_sec = sec2 - sec1;
  d_usec = usec2 - usec1;
  if (d_usec < 0) {
    d_sec -= 1;
    d_usec += 1000000;
  }
}



void print_time()
{
  int sec, min, hour;
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);

  tp.tv_sec -= 7*3600; // change to PST.
  hour = (tp.tv_sec/3600) % 24;
  min = (tp.tv_sec/60) % 60;
  sec = tp.tv_sec % 60;

  cout << "(" << hour << ":" << min << ":" << sec << ")";
}



bool is_pair1_greater_ii( const pair<int, int>& i, const pair<int, int>& j )
{
  return i.second > j.second;
}

bool is_pair1_smaller_ii( const pair<int, int>& i, const pair<int, int>& j )
{
  return j.second > i.second;
}


bool is_pair1_greater_id( const pair<int, double>& i, const pair<int, double>& j )
{
  return i.second > j.second;
}

bool is_pair1_smaller_id( const pair<int, double>& i, const pair<int, double>& j )
{
  return j.second > i.second;
}



bool is_pair1_greater_sd( const pair<string, double>& i, const pair<string, double>& j )
{
  return i.second > j.second;
}

bool is_pair1_smaller_sd( const pair<string, double>& i, const pair<string, double>& j )
{
  return j.second > i.second;
}




// I recommend using std::runtime_error instead of CmnException.
CmnException :: CmnException(const char* msg)
  : data_(msg)
{
}

CmnException :: CmnException(const string& msg)
  : data_(msg)
{
}

const char* CmnException :: what()
{
  return data_.c_str();
}



// This increases the stack size of the process from 8M to 64M.
bool increase_stack_size()
{
  const rlim_t kStackSize = 64L * 1024L * 1024L;   // min stack size = 64 Mb
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    rlim_t original_size = rl.rlim_cur;
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      int result2 = setrlimit(RLIMIT_STACK, &rl);
      if (result2 != 0) {
	cout << "setrlimit returned result = " << result2 << endl;
	return false;
      }

      cout << "Stack size increased from: " << original_size
	   << " to: " << rl.rlim_cur << endl;
    }
  }

  return true;
}


// This increases the stack size of the process from 8M to num_meg Megabytes.
bool increase_stack_size(unsigned long num_meg)
{
  const rlim_t kStackSize = num_meg * 1024L * 1024L;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    rlim_t original_size = rl.rlim_cur;
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      int result2 = setrlimit(RLIMIT_STACK, &rl);
      if (result2 != 0) {
	cout << "setrlimit returned result = " << result2 << endl;
	return false;
      }

      cout << "Stack size increased from: " << original_size
	   << " to: " << rl.rlim_cur << endl;
    }
  }

  return true;
}



// End CmnClass:
}

