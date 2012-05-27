#include "EIPrerequisites.h"

#ifdef HAVE_THREAD_H
    #include <thread>
    #include <mutex>
    namespace EI
    {
        namespace Thread
        {
            typedef std::thread thread;
            typedef std::mutex mutex;
            typedef std::lock_guard<std::mutex> lock_guard;
        }
    }
#else
    #include <boost/thread.hpp>
    #include <boost/thread/mutex.hpp>
    namespace EI
    {
        namespace Thread
        {
            typedef boost::thread thread;
            typedef boost::mutex mutex;
            typedef boost::lock_guard<boost::mutex> lock_guard;
        }
    }
#endif
