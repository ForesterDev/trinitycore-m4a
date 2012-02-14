#pragma once

#include <boost/thread/shared_mutex.hpp>

namespace Detail
{
    typedef boost::shared_mutex Vmap_mutex;

    inline Vmap_mutex &vmap_mutex()
    {
        static Vmap_mutex m;
        return m;
    }
}
