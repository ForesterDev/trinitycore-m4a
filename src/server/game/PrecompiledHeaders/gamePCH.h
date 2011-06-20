//add here most rarely modified headers to speed up debug build compilation

#include <cstddef>
#include <cstdint>
#include <memory>
#include <algorithm>
#include <utility>
#include <functional>
#include <array>
#include <limits>
#include <sstream>
#include <boost/thread/locks.hpp>
#include "WorldSocket.h"        // must be first to make ACE happy with ACE includes in it

#include "Common.h"

#include "MapManager.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectDefines.h"
#include "Opcodes.h"
#include "SharedDefines.h"
#include "ObjectMgr.h"
