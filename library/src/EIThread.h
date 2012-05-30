#include "EIPrerequisites.h"

#ifdef HAVE_THREAD_H
    #include <thread>
    #include <mutex>
    #include <condition_variable>
    namespace EI
    {
        namespace Thread
        {
            typedef std::thread thread;
            typedef std::mutex mutex;
            typedef std::lock_guard<std::mutex> lock_guard;
            typedef std::unique_lock<std::mutex> unique_lock;
            typedef std::condition_variable condition_variable;
        }
    }
#else
    #include <boost/thread.hpp>
    #include <boost/thread/mutex.hpp>
    #include <boost/thread/condition.hpp>
    namespace EI
    {
        namespace Thread
        {
            typedef boost::thread thread;
            typedef boost::mutex mutex;
            typedef boost::lock_guard<boost::mutex> lock_guard;
            typedef boost::unique_lock<boost::mutex> unique_lock;
            typedef boost::condition condition_variable;
        }
    }
#endif
