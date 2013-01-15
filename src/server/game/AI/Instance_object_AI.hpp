#pragma once

#include <utility>
#include <memory>
#include <stdexcept>

class Creature;
class InstanceScript;

namespace Detail
{
    InstanceScript *get_instance_script(Creature &creature);
}

template<class Instance,
        class Base_AI>
    class Instance_object_AI
    : public Base_AI
{
    typedef Instance_object_AI Myt;

public:
    typedef Instance Instance_type;

    template<class Cty>
        explicit Instance_object_AI(Cty &&c)
        : Base_AI(std::forward<Cty>(c)),
            instance_
                (dynamic_cast<Instance_type *>(Detail::get_instance_script(*Base_AI::me)))
    {
        if (instance_)
            ;
        else
            throw std::runtime_error("AI owner missing Instance");
    }

    Instance_object_AI(Myt &&right)
        : Base_AI(std::move(right.base_ai())),
            instance_(std::move(right.instance_))
    {
    }

    ~Instance_object_AI()
    {
    }

    Instance_type &instance()
    {
        return *instance_;
    }

    const Instance_type &instance() const
    {
        return *instance_;
    }

private:
    Base_AI &base_ai()
    {
        return *this;
    }

    const Base_AI &base_ai() const
    {
        return *this;
    }

    Instance_type *instance_;
};
