#include "stdafx.hpp"
#include "vmap_mutex.hpp"

vmap_mutex_type &vmap_mutex()
{
    static vmap_mutex_type m;
    return m;
}
