#pragma once

#include <mutex>

typedef std::mutex vmap_mutex_type;

vmap_mutex_type &vmap_mutex();
