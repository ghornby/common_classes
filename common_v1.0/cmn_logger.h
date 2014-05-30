/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/


#ifndef CMN_LOGGER
#define CMN_LOGGER


#include <iostream>
#include <string>
#include <sstream>


namespace CmnClass {


class Logger {
public:
  Logger();
  ~Logger();

  static void WriteTStoError();
  static std::ostream& Error();
  static std::ostream& Error(unsigned int level);
  static std::ostream& ErrorTS();
  static std::ostream& ErrorTS(unsigned int level);

  static std::ostream& ErrorDTS();
  static std::ostream& ErrorDTS(unsigned int level);


  static void WriteTStoMsg();
  static std::ostream& Msg();
  static std::ostream& Msg(unsigned int level);
  static std::ostream& MsgTS();
  static std::ostream& MsgTS(unsigned int level);
  static std::ostream& MsgDTS();
  static std::ostream& MsgDTS(unsigned int level);

  static void flush_log_error();
  static void set_min_error_level(unsigned int min);
  static void set_error_stream(std::ostream* ostr);
  static bool set_error_file(const char* fname);
  static bool set_error_file(const std::string& fname);

  static void flush_log_msg();
  static void set_min_msg_level(unsigned int min);
  static void set_msg_stream(std::ostream* ostr);
  static bool set_msg_file(const char* fname);
  static bool set_msg_file(const std::string& fname);

private:
  static bool is_error_file_open_;
  static bool is_msg_file_open_;
  static unsigned int min_error_level_;
  static unsigned int min_msg_level_;
  static std::ostream* error_ostr_;
  static std::ostream* msg_ostr_;

  static std::ostream cnull_; // See: http://stackoverflow.com/questions/6240950/platform-independent-dev-null-in-c

  static Logger* LogObj;
};



}

#endif


