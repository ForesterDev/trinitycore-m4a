#include "gamePCH.h"
#include "Instance_object_AI.hpp"
#include "Object.h"

namespace Detail
{
    InstanceData *get_instance_data(WorldObject &object)
    {
        return object.GetInstanceData();
    }
}
