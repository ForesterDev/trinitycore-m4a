#pragma once

#include <memory>
#include <utility>
#include <functional>
#include <Instance_boss_AI.hpp>
#include "ScriptedCreature.h"

class instance_ulduar;

class Yoggsaron_AI
    : public Instance_boss_AI<instance_ulduar, BossAI>
{
    typedef Instance_boss_AI<instance_ulduar, BossAI> Mybase;

public:
    friend struct npc_ys_thorimAI;
    friend struct npc_ys_mimironAI;

    enum Phases
    {
        PHASE_NULL = 0,
        PHASE_1,
        PHASE_2,
        PHASE_3
    };

    typedef void Reset_callback();

    explicit Yoggsaron_AI(Creature *c);

    ~Yoggsaron_AI();

    void UpdateAI(const uint32 diff);

    void Reset();

    void EnterCombat(Unit *enemy);

    void JustDied(Unit *);

private:
    void set_phase(Phases new_phase);

    void stopped();

    void turn_insane(Player &target);

    void mod_sanity(Player &target, int32 amount);

    void remove_sanity(Player &target);

    std::unique_ptr<Creature> voice;
    Phases phase;
    int summon_guardian_count;
};
