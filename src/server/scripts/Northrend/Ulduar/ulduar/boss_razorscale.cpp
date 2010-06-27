/*
 * Copyright (C) 2008 - 2009 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: razorscale
SDAuthor: MaXiMiUS
SD%Complete: 65
EndScriptData */

#include "ScriptPCH.h"
#include "ulduar.h"
#include "instance_ulduar.hpp"

//not in db
#define SAY_AGGRO                   -2000000
#define SAY_KILL                    -2000001
#define SAY_PHASE_2_TRANS           -2000002
#define SAY_PHASE_3_TRANS           -2000003
#define EMOTE_BREATH                -2000004

enum Spells
{
    SPELL_FLAMEBUFFET      = 64016,
    SPELL_FIREBALL         = 62796,

    SPELL_WINGBUFFET       = 62666,
    SPELL_FLAMEBREATH      = 63317,
    SPELL_FUSEARMOR        = 64771,
    SPELL_DEVOURINGFLAME   = 63014
};

enum Mobs
{
    NPC_DARK_RUNE_SENTINEL = 33846
};

struct boss_razorscaleAI : public BossAI
{
    boss_razorscaleAI(Creature *pCreature) : BossAI(pCreature, boss_razorscale) { }

    uint8 Phase;

    uint32 FlameBreathTimer;
    uint32 FuseArmorTimer;
    uint32 DevouringFlameTimer;
    uint32 FlameBuffetTimer;
    uint32 SummonAddsTimer;
    uint32 WingBuffetTimer;
    uint32 FireballTimer;

    bool InitialSpawn;
    bool IsFlying;

    void Reset()
    {
        Phase = 1;

        FlyPhase(Phase, 0);

        FlameBreathTimer = 20000;
        DevouringFlameTimer = 2000;
        FuseArmorTimer = 15000;
        FlameBuffetTimer = 3000;
        SummonAddsTimer = 45000;
        WingBuffetTimer = 17000;
        FireballTimer = 18000;

        InitialSpawn = true;
        IsFlying = true;

        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
        me->ApplySpellImmune(1, IMMUNITY_EFFECT,SPELL_EFFECT_ATTACK_ME, true);
    }

    void EnterCombat(Unit* /*who*/)
    {
        DoScriptText(SAY_AGGRO, me);
        DoZoneInCombat();
    }

    void JustDied(Unit* /*Killer*/)
    {
    }

    void KilledUnit(Unit * /*victim*/)
    {
        DoScriptText(SAY_KILL, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (me->GetPositionY() > -60 || me->GetPositionX() < 450) // Not Blizzlike, anti-exploit to prevent players from pulling bosses to vehicles.
        {
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(false);
            me->GetMotionMaster()->MoveTargetedHome();
        }

        // Victim is not controlled by a player (should never happen)
        if (me->getVictim() && !me->getVictim()->GetCharmerOrOwnerPlayerOrPlayerItself())
            me->Kill(me->getVictim());

        // todo: fix phase 1
        if (/* (me->GetHealth()*100 / me->GetMaxHealth()) < 99 && */ Phase == 1) // TODO: Only land (exit Phase 1) if brought down with harpoon guns! This is important!
        {
            Phase = 2;
            DoScriptText(SAY_PHASE_2_TRANS, me); // Audio: "Move quickly! She won't remain grounded for long!"
        }

        if ((me->GetHealth()*100 / me->GetMaxHealth()) < 33 && Phase == 2) // Health under 33%, Razorscale can't fly anymore.
        {
            Phase = 3;
            DoScriptText(SAY_PHASE_3_TRANS, me); // "Razorscale lands permanently!"
            // TODO: Cast Devouring Flame on all harpoon guns simultaneously, briefly after Phase 3 starts (lasts until the harpoon guns are destroyed)
        }

        FlyPhase(Phase, diff);

        if (Phase >= 2) // Ground Phase (Phase 3 = permanent ground phase)
        {
            if (FuseArmorTimer <= diff)
            {
                DoCastVictim(SPELL_FUSEARMOR);
                FuseArmorTimer = 10000;
            } else FuseArmorTimer -= diff;

            if (WingBuffetTimer <= diff)
            {
                DoCast(SPELL_WINGBUFFET);
                WingBuffetTimer = urand(7000,14000);
            } else WingBuffetTimer -= diff;

            if (FireballTimer <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                {
                    me->SetInFront(pTarget);
                    DoCast(pTarget, SPELL_FIREBALL);
                }

                FireballTimer = 18000;
            } else FireballTimer -= diff;

            if (FlameBreathTimer <= diff)
            {
                DoScriptText(EMOTE_BREATH, me); // TODO: "Razorscale takes a deep breath..."
                DoCastVictim(SPELL_FLAMEBREATH);
                FlameBreathTimer = 15000;
                WingBuffetTimer = 0;
            } else FlameBreathTimer -= diff;

            if (Phase == 3)
            {
                if (FlameBuffetTimer <= diff)
                {
                    DoScriptText(EMOTE_BREATH, me);
                    std::list<Unit*> pTargets;
                    SelectTargetList(pTargets, RAID_MODE(3,9), SELECT_TARGET_RANDOM, 100, true);
                    uint8 i = 0;
                    for (std::list<Unit*>::const_iterator itr = pTargets.begin(); itr != pTargets.end();)
                    {
                        if (me->HasInArc(M_PI, *itr))
                        {
                            DoCast(*itr, SPELL_FLAMEBUFFET, true);
                            ++i;
                        }
                        if (++itr == pTargets.end() || i == RAID_MODE(3,9))
                        {
                            AttackStart(*--itr); // seems to attack targets randomly during perma-ground phase..
                            break;
                        }
                    }
                    FlameBuffetTimer = 25000;
                } else FlameBuffetTimer -= diff;
            }

            DoMeleeAttackIfReady();
        }
        else if (Phase == 1) //Flying Phase
        {
            if (InitialSpawn)
                SummonAdds();

            InitialSpawn = false;

            if (FireballTimer <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                {
                    me->SetInFront(pTarget);
                    DoCast(pTarget, SPELL_FIREBALL);
                }
                FireballTimer = 18000;
            } else FireballTimer -= diff;

            if (DevouringFlameTimer <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                {
                    me->SetInFront(pTarget);
                    DoCast(pTarget, SPELL_DEVOURINGFLAME);
                }
                DevouringFlameTimer = 10000;
            } else DevouringFlameTimer -= diff;

            if (SummonAddsTimer <= diff)
                SummonAdds();
            else
                SummonAddsTimer -= diff;
        }
    }

    void SummonAdds()
    {
        // TODO: Adds will come in waves from mole machines. One mole can spawn a Dark Rune Watcher
        // with 1-2 Guardians, or a lone Sentinel. Up to 4 mole machines can spawn adds at any given time.
        uint8 random = urand(1,4);
        for (uint8 i = 0; i < random; ++i)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
            {
                float x = std::max(500.0f, std::min(650.0f, pTarget->GetPositionX() + irand(-20,20)));   // Safe range is between 500 and 650
                float y = std::max(-235.0f, std::min(-145.0f, pTarget->GetPositionY() + irand(-20,20))); // Safe range is between -235 and -145
                float z = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);                         // Ground level
                // TODO: Spawn drillers, then spawn adds 5 seconds later
                if (Creature *pAdd = me->SummonCreature(NPC_DARK_RUNE_SENTINEL, x, y, z, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
                    pAdd->AI()->AttackStart(pTarget);
            }
        }
        SummonAddsTimer = 45000;
    }

    void FlyPhase(uint8 Phase, const uint32 /*diff*/)
    {
        const float x = 587.54;
        const float y = -174.92;
        const float GroundLevel = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
        const float FlightHeight = GroundLevel + 4.0f; // TODO: Fly out of range of attacks (442 is sufficient height for this), minus ~(10*number of harpoon gun chains attached to Razorscale)

        if (Phase == 1) // Always flying during Phase 1
            IsFlying = true;

        me->SetFlying(IsFlying);
        me->SendMovementFlagUpdate();
        me->SetSpeed(MOVE_WALK, IsFlying ? 7.0f : 2.5f, IsFlying);

        if (Phase == 1) // Flying Phase
        {
            if (me->GetPositionZ() > FlightHeight) // Correct height, stop moving
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            else        // Incorrect height
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->GetMotionMaster()->MovePoint(0, x, y, FlightHeight + 0.5f); // Fly to slightly above (x, y, FlightHeight)
            }
        }
        else // Ground Phases
        {
            const float CurrentGroundLevel = me->GetBaseMap()->GetHeight(me->GetPositionX(), me->GetPositionY(), MAX_HEIGHT);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            if (IsFlying && me->GetPositionZ() > CurrentGroundLevel) // Fly towards the ground
                me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), CurrentGroundLevel);
                // TODO: Swoop up just before landing
            else
                IsFlying = false; // Landed, no longer flying
        }
    }
};

namespace
{
    bool expedition_commander_gossip_hello(Player *p, Creature *c)
    {
        if (auto i = dynamic_cast<instance_ulduar *>(c->GetInstanceData()))
        {
            if (!i->razorscale_state)
            {
                p->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_CHAT, "We are ready to help!");
                p->PlayerTalkClass->SendGossipMenu(14317, c->GetGUID());
            }
            return true;
        }
        else
            return false;
    }

    bool expedition_commander_gossip_select(Player *p, Creature *c, uint32, uint32 a)
    {
        if (auto i = dynamic_cast<instance_ulduar *>(c->GetInstanceData()))
        {
            p->PlayerTalkClass->CloseGossip();
            if (!i->razorscale_state)
                if (a == 0)
                {
                    c->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    i->razorscale_state = true;
                    // TODO: events
                    // Expedition Engineer yells: Give us a moment to prepare to build the turrets.
                    // <pause two seconds>
                    // Expedition Commander yells: Be on the lookout! Mole machines will be
                    //  surfacing soon with those nasty iron dwarves aboard!
                    // <Razorscale flies nearby and the encounter begins>
                    if (const auto &guid = i->uiRazorscaleGUID)
                        if (auto c = i->instance->GetCreature(guid))
                        {
                            c->SetHomePosition(587.54f, -174.92f, 442.f, 4.37237f);
                            c->GetMotionMaster()->MoveTargetedHome();
                        }
                }
            return true;
        }
        else
            return false;
    }
}

void AddSC_boss_razorscale()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_razorscale";
    newscript->GetAI = &get_ai<boss_razorscaleAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_expedition_commander";
    newscript->pGossipHello = &expedition_commander_gossip_hello;
    newscript->pGossipSelect = &expedition_commander_gossip_select;
    newscript->RegisterSelf();
}
