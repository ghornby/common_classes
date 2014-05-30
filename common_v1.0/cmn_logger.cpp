/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/


#include "cmn_logger.h"
#include "cmn_utils.h"

#include <fstream>
#include <iostream>
using namespace std;


namespace CmnClass {

bool Logger :: is_msg_file_open_ = false;
bool Logger :: is_error_file_open_ = false;
unsigned int Logger :: min_msg_level_ = 255;
unsigned int Logger :: min_error_level_ = 255;
ostream* Logger :: msg_ostr_ = &cout;
ostream* Logger :: error_ostr_ = &cerr;

std::ostream Logger :: cnull_(0);



void Logger :: WriteTStoMsg()
{
  if (msg_ostr_) {
    print_time(*msg_ostr_);
  }
}

void Logger :: WriteTStoError()
{
  if (error_ostr_) {
    print_time(*error_ostr_);
  }
}


ostream& Logger :: Msg()
{
  return *msg_ostr_;
}

ostream& Logger :: Msg(unsigned int level)
{
  if (level > min_msg_level_) {
    return cnull_;
  }

  return *msg_ostr_;
}


// Writes with a timestamp:
ostream& Logger :: MsgTS()
{
  print_time(*msg_ostr_);
  *msg_ostr_ << ":: ";
  return *msg_ostr_;
}

ostream& Logger :: MsgTS(unsigned int level)
{
  if (level > min_msg_level_) {
    return cnull_;
  }

  print_time(*msg_ostr_);
  *msg_ostr_ << ":: ";
  for (unsigned int i=0; i<level; i++) {
    *msg_ostr_ << "- ";
  }
  return *msg_ostr_;
}


// Writes with a timestamp:
ostream& Logger :: MsgDTS()
{
  print_datetime(*msg_ostr_);
  *msg_ostr_ << ":: ";
  return *msg_ostr_;
}

ostream& Logger :: MsgDTS(unsigned int level)
{
  if (level > min_msg_level_) {
    return cnull_;
  }

  print_datetime(*msg_ostr_);
  *msg_ostr_ << ":: ";
  for (unsigned int i=0; i<level; i++) {
    *msg_ostr_ << "- ";
  }
  return *msg_ostr_;
}




ostream& Logger :: Error()
{
  return *error_ostr_;
}

ostream& Logger :: Error(unsigned int level)
{
  if (level > min_error_level_) {
    return cnull_;
  }

  return *error_ostr_;
}

ostream& Logger :: ErrorTS()
{
  print_time(*error_ostr_);
  *error_ostr_ << ":: ";
  return *error_ostr_;
}


// Prints timestamp.
ostream& Logger :: ErrorTS(unsigned int level)
{
  if (level > min_error_level_) {
    return cnull_;
  }

  print_time(*error_ostr_);
  *error_ostr_ << ":: ";
  for (unsigned int i=0; i<level; i++) {
    *error_ostr_ << "- ";
  }
  return *error_ostr_;
}



// Prints date and timestampe.
ostream& Logger :: ErrorDTS()
{
  print_datetime(*error_ostr_);
  *error_ostr_ << ":: ";
  return *error_ostr_;
}


// Prints date and timestampe.
ostream& Logger :: ErrorDTS(unsigned int level)
{
  if (level > min_error_level_) {
    return cnull_;
  }

  print_datetime(*error_ostr_);
  *error_ostr_ << ":: ";
  for (unsigned int i=0; i<level; i++) {
    *error_ostr_ << "- ";
  }
  return *error_ostr_;
}



void Logger :: flush_log_msg()
{
  msg_ostr_->flush();
}

void Logger :: set_min_msg_level(unsigned int level)
{
  min_msg_level_ = level;
}

void Logger :: set_msg_stream(ostream* ostr)
{
  if (ostr == msg_ostr_) {
    return;
  }

  Logger::flush_log_msg();
  if (is_msg_file_open_) {
    ((ofstream*)(msg_ostr_))->close();
    is_msg_file_open_ = false;
  }
  msg_ostr_ = ostr;
}

bool Logger :: set_msg_file(const char* fname)
{
  ofstream* file = new ofstream(fname, ios::out | ios::app);
  if (!file->is_open()) {
    return false;
  }

  set_msg_stream(file);
  Logger::is_msg_file_open_ = true;
  return true;
}

bool Logger :: set_msg_file(const string& fname)
{
  return set_msg_file(fname.c_str());
}





void Logger :: flush_log_error()
{
  error_ostr_->flush();

}

void Logger :: set_min_error_level(unsigned int level)
{
  min_error_level_ = level;
}

void Logger :: set_error_stream(ostream* ostr)
{
  if (ostr == error_ostr_) {
    return;
  }

  Logger::flush_log_error();
  if (is_error_file_open_) {
    ((ofstream*)(error_ostr_))->close();
    is_error_file_open_ = false;
  }
  error_ostr_ = ostr;
}

bool Logger :: set_error_file(const char* fname)
{
  ofstream* file = new ofstream(fname, ios::app);
  if (!file->is_open()) {
    return false;
  }
  set_error_stream(file);
  Logger::is_error_file_open_ = true;
  return true;
}

bool Logger :: set_error_file(const string& fname)
{
  return set_error_file(fname.c_str());
}




Logger* LogObj = new Logger();

Logger :: Logger()
{
  //  Logger::Msg() << "logger created." << endl;
}


Logger :: ~Logger()
{
  Logger::Msg() << "logger destroyed." << endl;
  flush_log_msg();
  flush_log_error();

  if (is_msg_file_open_) {
    flush_log_msg();
    ((ofstream*)(msg_ostr_))->close();
    is_msg_file_open_ = false;
  }

  if (is_error_file_open_) {
    flush_log_error();
    ((ofstream*)(error_ostr_))->close();
    is_error_file_open_ = false;
  }
}




}
