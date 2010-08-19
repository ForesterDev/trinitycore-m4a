#pragma once

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

    void UpdateAI(const uint32 diff);

    void Reset();

    void EnterCombat(Unit *enemy);

    void JustDied(Unit *);

private:
    instance_ulduar &ulduar();

    const instance_ulduar &ulduar() const;

    void set_phase(Phases new_phase);

    void stopped();

    Phases phase;
};
