#include "gamePCH.h"
#include "Instance_object_AI.hpp"
#include "Creature.h"

namespace Detail
{
    InstanceScript *get_instance_script(Creature &creature)
    {
        return creature.GetInstanceScript();
    }
}
