/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/


#ifndef CMN_NIX_MUTEX_H
#define CMN_NIX_MUTEX_H

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
#include <string>

namespace CmnClass
{
  class Mutex
  {
  public:
      Mutex();
      ~Mutex();
      void lock();
      bool tryLock(int timeout = 0);
      void unlock();

  protected:
  #ifdef _WIN32
      HANDLE m_mutex;
  #else
      pthread_mutex_t m_mutex;
  #endif
      static int counter;
  };
}

#endif // NIX_MUTEX_H
