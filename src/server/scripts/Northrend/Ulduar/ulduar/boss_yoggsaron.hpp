#pragma once

#include <memory>
#include <utility>
#include <functional>
#include "ScriptedCreature.h"
#include "ulduar.h"

class instance_ulduar;

class Yoggsaron_AI
    : public BossAI
{
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

    Yoggsaron_AI(Creature *c);

    ~Yoggsaron_AI();

    void UpdateAI(const uint32 diff);

    void Reset();

    void EnterCombat(Unit *enemy);

    void JustDied(Unit *);

private:
    instance_ulduar &ulduar();

    const instance_ulduar &ulduar() const;

    void set_phase(Phases new_phase);

    void stopped();

    void turn_insane(Player &target);

    void mod_sanity(Player &target, int32 amount);

    void remove_sanity(Player &target);

    std::unique_ptr<Creature> voice;
    Phases phase;
    int summon_guardian_count;
};
