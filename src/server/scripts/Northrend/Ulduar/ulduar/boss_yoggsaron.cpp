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
SDName: Yogg-Saron
SDAuthor: PrinceCreed
SD%Complete: 25
SDComments: Keeper's scripts completed
EndScriptData */

#include "ScriptPCH.h"
#include "boss_yoggsaron.hpp"
#include <Instance_object_AI.hpp>
#include "ulduar.h"
#include "instance_ulduar.hpp"

namespace
{
    enum
    {
        event_sara_prefight,
        event_apply_sanity,
        event_close_door,
        event_turn_outside_players,
        event_berserk,
        event_extinguish_all_life,
        event_summon_guardian,
    };

    enum
    {
        sara_prefight_interval = 1000 * 60 * 60
    };

    const char *berserk_text()
    {
        return "%s goes berserk, extinguishing all life!";
    }
}

enum Sara_Yells
{
    SAY_SARA_PREFIGHT_1                         = -1603310,
    SAY_SARA_PREFIGHT_2                         = -1603311,
    SAY_SARA_AGGRO_1                            = -1603312,
    SAY_SARA_AGGRO_2                            = -1603313,
    SAY_SARA_AGGRO_3                            = -1603314,
    SAY_SARA_SLAY_1                             = -1603315,
    SAY_SARA_SLAY_2                             = -1603316,
    WHISP_SARA_INSANITY                         = -1603317,
    SAY_SARA_PHASE2_1                           = -1603318,
    SAY_SARA_PHASE2_2                           = -1603319,
};

enum YoggSaron_Yells
{
    SAY_PHASE2_1                                = -1603330,
    SAY_PHASE2_2                                = -1603331,
    SAY_PHASE2_3                                = -1603332,
    SAY_PHASE2_4                                = -1603333,
    SAY_PHASE2_5                                = -1603334,
    SAY_PHASE3                                  = -1603335,
    SAY_VISION                                  = -1603336,
    SAY_SLAY_1                                  = -1603337,
    SAY_SLAY_2                                  = -1603338,
    WHISP_INSANITY_1                            = -1603339,
    WHISP_INSANITY_2                            = -1603340,
    SAY_DEATH                                   = -1603341,
};

namespace
{
    // Images of Keepers
    enum Npcs
    {
        NPC_IMAGE_OF_FREYA                          = 33241,
        NPC_IMAGE_OF_THORIM                         = 33242,
        NPC_IMAGE_OF_MIMIRON                        = 33244,
        NPC_IMAGE_OF_HODIR                          = 33213,
    
        NPC_SANITY_WELL                             = 33991,
    
        NPC_GUARDIAN_OF_YOGGSARON                   = 33136,
        NPC_CRUSHER_TENTACLE                        = 33966,
        NPC_CORRUPTOR_TENTACLE                      = 33985,
        NPC_CONSTRICTOR_TENTACLE                    = 33983,
        NPC_DESCEND_INTO_MADNESS                    = 34072,

        NPC_LAUGHING_SKULL                          = 33990,
        NPC_INFLUENCE_TENTACLE                      = 33943,
        NPC_IMMORTAL_GUARDIAN                       = 33988,

        NPC_YOGG_SARON_BRAIN                        = 33890,
        NPC_SUIT_OF_ARMOR                           = 33433,
        NPC_AZURE_CONSORT                           = 33717,
        NPC_EMERALD_CONSORT                         = 33719,
        NPC_OBSIDIAN_CONSORT                        = 33720,
        NPC_RUBY_CONSORT                            = 33716,
        NPC_DEATHSWORN_ZEALOT                       = 33567,
        NPC_OMINOUS_CLOUD                           = 33292
    };
}

#define GOSSIP_KEEPER_HELP                      "I need your help."

enum Keepers_Yells
{
    SAY_MIMIRON_HELP                            = -1603259,
    SAY_FREYA_HELP                              = -1603189,
    SAY_THORIM_HELP                             = -1603287,
    SAY_HODIR_HELP                              = -1603217,
};

namespace
{
    enum
    {
        spell_sanity = 63050 /* Sanity */
    };
}

enum Keepers_Spells
{
    SPELL_KEEPER_ACTIVE                         = 62647,
    
    // Freya
    SPELL_RESILIENCE_OF_NATURE                  = 62670,
    SPELL_SANITY_WELL_SPAWN                     = 64170,
    SPELL_SANITY_WELL_VISUAL                    = 63288,
    SPELL_SANITY_WELL                           = 64169,
    
    // Thorim
    SPELL_FURY_OF_THE_STORMS                    = 62702,
    SPELL_TITANIC_STORM                         = 64171,
    SPELL_TITANIC_STORM_DEBUFF                  = 64162,
    
    // Mimiron
    SPELL_SPEED_OF_INVENTION                    = 62671,
    SPELL_DESTABILIZATION                       = 65210,
    SPELL_DESTABILIZATION_DEBUFF                = 65206,
    
    // Hodir
    SPELL_FORTITUDE_OF_FROST                    = 62650,
    SPELL_PROTECTIVE_GAZE                       = 64174
};

const Position SanityWellPos[10] =
{
{2008.38,35.41,331.251,0},
{1990.63,50.35,332.041,0},
{1973.40,41.09,330.989,0},
{1973.12,-90.27,330.14,0},
{1994.26,-96.62,330.62,0},
{2005.41,-82.88,329.50,0},
{2042.09,-41.70,329.12,0},
{1918.06,16.50,330.970,0},
{1899.59,-4.87,332.137,0},
{1897.75,-48.24,332.35,0}
};

namespace
{
    struct Sara_AI
        : Instance_object_AI<instance_ulduar, ScriptedAI>
    {
        typedef Instance_object_AI<instance_ulduar, ScriptedAI> Mybase;

        explicit Sara_AI(Creature *c)
            : Mybase(c)
        {
        }

        Sara_AI(Sara_AI &&right)
            : Mybase(std::move(right))
        {
        }

        void DamageTaken(Unit *, uint32 &damage)
        {
            auto health = me->GetHealth();
            if (damage < health)
                ;
            else
                damage = health - 1;
        }
    };

    struct Guardian_of_yoggsaron_AI
        : Instance_object_AI<instance_ulduar, ScriptedAI>
    {
        typedef Instance_object_AI<instance_ulduar, ScriptedAI> Mybase;

        explicit Guardian_of_yoggsaron_AI(Creature *c)
            : Mybase(c)
        {
        }

        void DamageTaken(Unit *, uint32 &damage)
        {
        }
    };
}

/*------------------------------------------------------*
 *                  Images of Keepers                   *
 *------------------------------------------------------*/
 
struct keeper_imageAI : public ScriptedAI
{
    keeper_imageAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceScript();
    }

    InstanceScript *pInstance;
};

bool GossipHello_keeper_image(Player* pPlayer, Creature* pCreature)
{
    InstanceScript *data = pPlayer->GetInstanceScript();
    InstanceScript *pInstance = pCreature->GetInstanceScript();
    
    if (pInstance && pPlayer)
    {
        if (!pCreature->HasAura(SPELL_KEEPER_ACTIVE))
        {
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_KEEPER_HELP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        }
    }
    return true;
}

bool GossipSelect_keeper_image(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    InstanceScript *data = pPlayer->GetInstanceScript();
    InstanceScript *pInstance = pCreature->GetInstanceScript();
    
    if (pPlayer)
        pPlayer->CLOSE_GOSSIP_MENU();
        
    switch (pCreature->GetEntry())
    {
        case NPC_IMAGE_OF_FREYA:
            DoScriptText(SAY_FREYA_HELP, pCreature);
            pCreature->CastSpell(pCreature, SPELL_KEEPER_ACTIVE, true);
            if (Creature *pFreya = pCreature->GetCreature(*pCreature, pInstance->GetData64(DATA_YS_FREYA)))
                pFreya->SetVisible(true);
            break;
        case NPC_IMAGE_OF_THORIM:
            DoScriptText(SAY_THORIM_HELP, pCreature);
            pCreature->CastSpell(pCreature, SPELL_KEEPER_ACTIVE, true);
            if (Creature *pThorim = pCreature->GetCreature(*pCreature, pInstance->GetData64(DATA_YS_THORIM)))
                pThorim->SetVisible(true);
            break;
        case NPC_IMAGE_OF_MIMIRON:
            DoScriptText(SAY_MIMIRON_HELP, pCreature);
            pCreature->CastSpell(pCreature, SPELL_KEEPER_ACTIVE, true);
            if (Creature *pMimiron = pCreature->GetCreature(*pCreature, pInstance->GetData64(DATA_YS_MIMIRON)))
                pMimiron->SetVisible(true);
            break;
        case NPC_IMAGE_OF_HODIR:
            DoScriptText(SAY_HODIR_HELP, pCreature);
            pCreature->CastSpell(pCreature, SPELL_KEEPER_ACTIVE, true);
            if (Creature *pHodir = pCreature->GetCreature(*pCreature, pInstance->GetData64(DATA_YS_HODIR)))
                pHodir->SetVisible(true);
            break;
    }
    return true;
}

CreatureAI* GetAI_keeper_image(Creature* pCreature)
{
    return new keeper_imageAI (pCreature);
}


struct npc_ys_freyaAI : public ScriptedAI
{
    npc_ys_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceScript();
        me->SetReactState(REACT_PASSIVE);
        me->SetVisible(false);
    }

    InstanceScript *pInstance;
    int32 WellTimer;

    void Reset()
    {
        WellTimer = urand(5000, 10000);
    }
    
    void EnterCombat()
    {
        DoCast(me, SPELL_RESILIENCE_OF_NATURE);
    }
    
    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;
            
        if (WellTimer <= uiDiff)
        {
            DoCast(SPELL_SANITY_WELL_SPAWN);
            me->SummonCreature(NPC_SANITY_WELL, SanityWellPos[rand()%10], TEMPSUMMON_TIMED_DESPAWN, 60000);
            WellTimer = 15000;
        }
        else WellTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_ys_freya(Creature* pCreature)
{
    return new npc_ys_freyaAI(pCreature);
}

struct npc_sanity_wellAI : public Scripted_NoMovementAI
{
    npc_sanity_wellAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        pInstance = pCreature->GetInstanceScript();
        DoCast(me, SPELL_SANITY_WELL_VISUAL);
        DoCast(me, SPELL_SANITY_WELL);
    }

    InstanceScript *pInstance;
};

CreatureAI* GetAI_npc_sanity_well(Creature* pCreature)
{
    return new npc_sanity_wellAI(pCreature);
}

struct npc_ys_thorimAI
    : public Instance_object_AI<instance_ulduar, ScriptedAI>
{
    typedef Instance_object_AI<instance_ulduar, ScriptedAI> Mybase;

    npc_ys_thorimAI(Creature *pCreature)
        : Mybase(pCreature),
            phase(Yoggsaron_AI::PHASE_NULL)
    {
        pInstance = pCreature->GetInstanceScript();
        if (auto ys = instance().yoggsaron())
            if (auto ai = dynamic_cast<Yoggsaron_AI *>(ys->AI()))
                phase = ai->phase;
        me->SetReactState(REACT_PASSIVE);
        me->SetVisible(false);
    }

    InstanceScript *pInstance;
    Yoggsaron_AI::Phases phase;

    void Reset(){}
    
    void EnterCombat()
    {
        DoCast(me, SPELL_FURY_OF_THE_STORMS);
    }
    
    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
            return;
            
        if (!me->HasAura(SPELL_TITANIC_STORM) && phase == Yoggsaron_AI::PHASE_3)
            DoCast(me, SPELL_TITANIC_STORM);
    }
};

CreatureAI* GetAI_npc_ys_thorim(Creature* pCreature)
{
    return new npc_ys_thorimAI(pCreature);
}

struct npc_ys_mimironAI
    : public Instance_object_AI<instance_ulduar, ScriptedAI>
{
    typedef Instance_object_AI<instance_ulduar, ScriptedAI> Mybase;

    npc_ys_mimironAI(Creature *pCreature)
        : Mybase(pCreature),
            phase(Yoggsaron_AI::PHASE_NULL)
    {
        pInstance = pCreature->GetInstanceScript();
        if (auto ys = instance().yoggsaron())
            if (auto ai = dynamic_cast<Yoggsaron_AI *>(ys->AI()))
                phase = ai->phase;
        me->SetReactState(REACT_PASSIVE);
        me->SetVisible(false);
    }

    InstanceScript *pInstance;
    Yoggsaron_AI::Phases phase;
    int32 DestabilizeTimer;

    void Reset()
    {
        DestabilizeTimer = 15000;
    }
    
    void EnterCombat()
    {
        DoCast(me, SPELL_SPEED_OF_INVENTION);
    }
    
    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;
            
        if (DestabilizeTimer <= uiDiff)
        {
            if (phase == Yoggsaron_AI::PHASE_2)
                DoCast(SPELL_DESTABILIZATION);
            DestabilizeTimer = 15000;
        }
        else DestabilizeTimer -= uiDiff;            
    }
};

CreatureAI* GetAI_npc_ys_mimiron(Creature* pCreature)
{
    return new npc_ys_mimironAI(pCreature);
}

struct npc_ys_hodirAI : public ScriptedAI
{
    npc_ys_hodirAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceScript();
        me->SetReactState(REACT_PASSIVE);
        me->SetVisible(false);
    }

    InstanceScript *pInstance;

    void Reset(){}
    
    void EnterCombat()
    {
        DoCast(me, SPELL_FORTITUDE_OF_FROST);
    }
    
    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;
    }
};

CreatureAI* GetAI_npc_ys_hodir(Creature* pCreature)
{
    return new npc_ys_hodirAI(pCreature);
}

void AddSC_boss_yogg_saron()
{
    struct Boss_sara
        : CreatureScript
    {
        Boss_sara()
            : CreatureScript("boss_sara")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return new Sara_AI(std::move(creature));
        }
    };
    new Boss_sara;
    struct Mob_guardian_of_yoggsaron
        : CreatureScript
    {
        Mob_guardian_of_yoggsaron()
            : CreatureScript("mob_guardian_of_yoggsaron")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return new Guardian_of_yoggsaron_AI(std::move(creature));
        }
    };
    new Mob_guardian_of_yoggsaron;
    struct NPC_keeper_image
        : CreatureScript
    {
        NPC_keeper_image()
            : CreatureScript("npc_keeper_image")
        {
        }

        bool OnGossipHello(Player *player, Creature *creature)
        {
            return GossipHello_keeper_image(std::move(player), std::move(creature));
        }

        bool OnGossipSelect
            (Player *player, Creature *creature, uint32 sender, uint32 action)
        {
            return GossipSelect_keeper_image(std::move(player), std::move(creature),
                    std::move(sender), std::move(action));
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return GetAI_keeper_image(std::move(creature));
        }
    };
    new NPC_keeper_image;
    
    struct NPC_ys_freya
        : CreatureScript
    {
        NPC_ys_freya()
            : CreatureScript("npc_ys_freya")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return GetAI_npc_ys_freya(std::move(creature));
        }
    };
    new NPC_ys_freya;
    
    struct NPC_ys_thorim
        : CreatureScript
    {
        NPC_ys_thorim()
            : CreatureScript("npc_ys_thorim")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return GetAI_npc_ys_thorim(std::move(creature));
        }
    };
    new NPC_ys_thorim;
    
    struct NPC_ys_mimiron
        : CreatureScript
    {
        NPC_ys_mimiron()
            : CreatureScript("npc_ys_mimiron")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return GetAI_npc_ys_mimiron(std::move(creature));
        }
    };
    new NPC_ys_mimiron;
    
    struct NPC_ys_hodir
        : CreatureScript
    {
        NPC_ys_hodir()
            : CreatureScript("npc_ys_hodir")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return GetAI_npc_ys_hodir(std::move(creature));
        }
    };
    new NPC_ys_hodir;
    
    struct NPC_sanity_well
        : CreatureScript
    {
        NPC_sanity_well()
            : CreatureScript("npc_sanity_well")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return GetAI_npc_sanity_well(std::move(creature));
        }
    };
    new NPC_sanity_well;
    struct Boss_yoggsaron
        : CreatureScript
    {
        Boss_yoggsaron()
            : CreatureScript("boss_yoggsaron")
        {
        }

        CreatureAI *GetAI(Creature *creature) const
        {
            return new Yoggsaron_AI(std::move(creature));
        }
    };
    new Boss_yoggsaron;
}

Yoggsaron_AI::Yoggsaron_AI(Creature *c)
    : Mybase(c, static_cast<uint32>(BOSS_YOGGSARON)),
        voice(new Creature)
{
    me->SetReactState(REACT_PASSIVE);
    if (voice->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), me->GetMap(), PHASEMASK_ANYWHERE, 33280 /* Voice of Yogg-Saron */, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f))
        ;
    else
        voice = nullptr;
}

Yoggsaron_AI::~Yoggsaron_AI()
{
}

void Yoggsaron_AI::UpdateAI(uint32 diff)
{
    events.Update(diff);
    while (auto event_ = events.GetEvent())
        switch (event_)
        {
        case event_sara_prefight:
            events.RepeatEvent(sara_prefight_interval);
            if (auto sara = instance().sara())
                DoScriptText(RAND(SAY_SARA_PREFIGHT_1, SAY_SARA_PREFIGHT_2), sara);
            break;
        case event_apply_sanity:
            events.PopEvent();
            {
                auto &players = instance().instance->GetPlayers();
                for (auto it = players.begin(), last = players.end(); it != last; )
                    if (auto p = it++->getSource())
                        if (auto a = p->AddAura(spell_sanity, p))
                            a->ModStackAmount(100 - 1);
            }
            break;
        case event_close_door:
            events.PopEvent();
            if (auto door = instance().yoggsaron_door())
            {
                door->setActive(true);
                door->SetGoState(GO_STATE_READY);
            }
            break;
        case event_turn_outside_players:
            events.PopEvent();
            {
                auto &players = instance().instance->GetPlayers();
                for (auto it = players.begin(), last = players.end(); it != last; )
                    if (auto p = it++->getSource())
                        if (p->wmo_id() == 47478 /* The Prison of Yogg-Saron */)
                            ;
                        else
                            remove_sanity(*p);
            }
            break;
        case event_berserk:
            events.PopEvent();
            me->MonsterTextEmote(berserk_text(), uint64(), true);
            events.ScheduleEvent(event_extinguish_all_life, 0);
            break;
        case event_extinguish_all_life:
            events.RepeatEvent(1500);
            DoCast(64166 /* Extinguish All Life */);
            break;
        case event_summon_guardian:
            {
                uint32 time;
                if (summon_guardian_count < 3)
                    time = 1000 * 20;
                else
                    time = 1000 * urand(10, 19);
                events.RepeatEvent(std::move(time));
            }
            ++summon_guardian_count;
            DoCast(62978 /* Summon Guardian */);
            break;
        default:
            ASSERT(false);
        }
    UpdateVictim();
}

void Yoggsaron_AI::Reset()
{
    me->SetVisible(false);
    set_phase(PHASE_NULL);
    stopped();
    BossAI::Reset();
    events.ScheduleEvent(event_sara_prefight, sara_prefight_interval);
    auto &in = instance();
    if (auto sara = in.sara())
    {
        sara->setFaction(35);
        sara->GetMotionMaster()->MoveTargetedHome();
        sara->SetVisible(true);
    }
    {
        auto p = in.ominous_clouds();
        std::for_each(p.first, p.second,
                std::bind(&Creature::Respawn, std::placeholders::_1, false));
    }
    in.connect_prison();
}

void Yoggsaron_AI::EnterCombat(Unit *enemy)
{
    auto &in = instance();
    in.disconnect_prison();
    BossAI::EnterCombat(enemy);
    events.CancelEvent(event_sara_prefight);
    events.ScheduleEvent(event_apply_sanity, 1000 * 2);
    events.ScheduleEvent(event_close_door, 1000 * 10);
    events.ScheduleEvent(event_turn_outside_players, 1000 * 15);
    events.ScheduleEvent(event_berserk, 1000 * 60 * 15);
    set_phase(PHASE_1);
    summon_guardian_count = 0;
    events.ScheduleEvent(event_summon_guardian, 0);
    if (auto sara = in.sara())
        DoScriptText(SAY_SARA_AGGRO_1, sara);
}

void Yoggsaron_AI::JustDied(Unit *killer)
{
    DoScriptText(SAY_DEATH, me);
    stopped();
    BossAI::JustDied(killer);
}

void Yoggsaron_AI::set_phase(Phases new_phase)
{
    phase = std::move(new_phase);
    auto &in = instance();
    if (auto mimiron = in.ys_mimiron())
        if (auto ai = dynamic_cast<npc_ys_mimironAI *>(mimiron->AI()))
            ai->phase = phase;
    if (auto thorim = in.ys_thorim())
        if (auto ai = dynamic_cast<npc_ys_thorimAI *>(thorim->AI()))
            ai->phase = phase;
}

void Yoggsaron_AI::stopped()
{
    auto &in = instance();
    if (auto door = in.yoggsaron_door())
    {
        door->SetGoState(GO_STATE_ACTIVE);
        door->setActive(false);
    }
    {
        auto &players = in.instance->GetPlayers();
        for (auto it = players.begin(), last = players.end(); it != last; )
            if (auto p = it++->getSource())
                p->RemoveAura(spell_sanity);
    }
}

void Yoggsaron_AI::turn_insane(Player &target)
{
    if (voice)
        DoScriptText(RAND(WHISP_INSANITY_1, WHISP_INSANITY_2), voice.get(), &target);
    me->CastSpell(&target, 63120 /* Insane */, true);
}

void Yoggsaron_AI::mod_sanity(Player &target, int32 amount)
{
    if (auto a = target.GetAura(spell_sanity))
        if (a->ModStackAmount(amount))
            turn_insane(target);
}

void Yoggsaron_AI::remove_sanity(Player &target)
{
    if (target.HasAura(spell_sanity))
    {
        target.RemoveAura(spell_sanity);
        turn_insane(target);
    }
}
