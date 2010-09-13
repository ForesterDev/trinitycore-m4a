#include "gamePCH.h"
#include "Instance_object_AI.hpp"
#include "Object.h"

namespace Detail
{
    InstanceScript *get_instance_script(WorldObject &object)
    {
        return object.GetInstanceScript();
    }
}
