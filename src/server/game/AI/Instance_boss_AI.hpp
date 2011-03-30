#pragma once

#include <utility>
#include <memory>
#include <stdexcept>

template<class Instance,
        class Base_AI>
    class Instance_boss_AI
    : public Base_AI
{
    typedef Instance_boss_AI Myt;

public:
    typedef Instance Instance_type;

    template<class Cty,
            class IDty>
        Instance_boss_AI(Cty &&c, IDty &&id)
        : Base_AI(std::forward<Cty>(c), std::forward<IDty>(id))
    {
        if (dynamic_cast<Instance_type *>(boss_ai().instance))
            ;
        else
            throw std::runtime_error("BossAI missing Instance");
    }

    Instance_boss_AI(Myt &&right)
        : Base_AI(std::move(right.base_ai()))
    {
    }

    ~Instance_boss_AI()
    {
    }

    Instance_type &instance()
    {
        return *static_cast<Instance_type *>(boss_ai().instance);
    }

    const Instance_type &instance() const
    {
        return *static_cast<const Instance_type *>(boss_ai().instance);
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

    BossAI &boss_ai()
    {
        return *this;
    }

    const BossAI &boss_ai() const
    {
        return *this;
    }
};
