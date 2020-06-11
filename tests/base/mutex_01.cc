// ---------------------------------------------------------------------
//
// Copyright (C) 2009 - 2018 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------


// verify that mutexes work correctly in MT context

#include <deal.II/base/thread_management.h>

#include "../tests.h"


Threads::Mutex mutex;


void
test()
{
  // get the mutex, but note that it is first
  // held by main() which will therefore
  // usually get to write to deallog first
  mutex.acquire();
  deallog << "2" << std::endl;
}


int
main()
{
  initlog();

#ifdef DEAL_II_WITH_THREADS

  mutex.acquire();

  Threads::Thread<> t = Threads::new_thread(&test);

  std::this_thread::sleep_for(std::chrono::seconds(2));
  deallog << "1" << std::endl;

  mutex.release();
  t.join();

  // the other thread should now have acquired the mutex, so release it
  // again (destroying an acquired lock invokes undefined behavior in
  // pthread_mutex_destroy)
  mutex.release();

#else

  // make sure the test also works in non-MT mode
  deallog << "1" << std::endl;
  deallog << "2" << std::endl;
#endif
}