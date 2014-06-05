/***

This file is part of the CommonClasses C++ library originally developed
by Gregory Hornby.

This code is released under the BSD-3 license:
  http://opensource.org/licenses/BSD-3-Clause
See the file "license.txt" in the root directory for full details.

***/


#include "cmn_mutex.h"

#include <iostream>
using namespace std;

namespace CmnClass
{
  Mutex::Mutex()
  {
#ifdef _WIN32
    m_mutex = CreateMutex(NULL, FALSE, NULL);
#else
    int ret_val = pthread_mutex_init(&m_mutex, 0);
    if (ret_val != 0) {
      cout << "mutex initialization error: " << ret_val << endl;
    }
#endif
  }

  Mutex::~Mutex()
  {
#ifdef _WIN32
    CloseHandle(m_mutex);
#else
    pthread_mutex_destroy(&m_mutex);
#endif
  }

  void Mutex::lock()
  {
#ifdef _WIN32
    DWORD waitResult = WaitForSingleObject(m_mutex, INFINITE);
#else
    pthread_mutex_lock(&m_mutex);
#endif
  }

  bool Mutex::tryLock(int timeout)
  {
#ifdef _WIN32
    return (WaitForSingleObject(m_mutex, timeout) == WAIT_OBJECT_0);
#else
    //NOTE: timeout is ignored for Unix.
    return (pthread_mutex_trylock(&m_mutex) == 0);
#endif
  }

  void Mutex::unlock()
  {
#ifdef _WIN32
    ReleaseMutex(m_mutex);
#else
    pthread_mutex_unlock(&m_mutex);
#endif
  }
}
