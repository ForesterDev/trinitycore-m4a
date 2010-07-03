/*
 * Copyright (C) 2008 - 2010 Trinity <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "ulduar.h"

enum Yells
{
    SAY_AGGRO                                   = -1603180,
    SAY_AGGRO_WITH_ELDER                        = -1603181,
    SAY_SLAY_1                                  = -1603182,
    SAY_SLAY_2                                  = -1603183,
    SAY_DEATH                                   = -1603184,
    SAY_BERSERK                                 = -1603185,
    SAY_SUMMON_CONSERVATOR                      = -1603186,
    SAY_SUMMON_TRIO                             = -1603187,
    SAY_SUMMON_LASHERS                          = -1603188,
    SAY_YS_HELP                                 = -1603189,

    // Elder Brightleaf
    SAY_BRIGHTLEAF_AGGRO                        = -1603190,
    SAY_BRIGHTLEAF_SLAY_1                       = -1603191,
    SAY_BRIGHTLEAF_SLAY_2                       = -1603192,
    SAY_BRIGHTLEAF_DEATH                        = -1603193,

    // Elder Ironbranch
    SAY_IRONBRANCH_AGGRO                        = -1603194,
    SAY_IRONBRANCH_SLAY_1                       = -1603195,
    SAY_IRONBRANCH_SLAY_2                       = -1603196,
    SAY_IRONBRANCH_DEATH                        = -1603197,

    // Elder Stonebark
    SAY_STONEBARK_AGGRO                         = -1603198,
    SAY_STONEBARK_SLAY_1                        = -1603199,
    SAY_STONEBARK_SLAY_2                        = -1603200,
    SAY_STONEBARK_DEATH                         = -1603201,
};

enum
{
    // Con-speed-atory timed achievement.
    // TODO Should be started when 1st trash is killed.
    ACHIEV_CON_SPEED_ATORY_START_EVENT            = 21597,
    SPELL_ACHIEVEMENT_CHECK                       = 65074,

    // Lumberjacked timed achievement.
    // TODO should be started when 1st elder is killed.
    // Spell should be casted when 3rd elder is killed.
    ACHIEV_LUMBERJACKED                           = 21686,
    SPELL_LUMBERJACKED_ACHIEVEMENT_CHECK          = 65296,
};

#define EMOTE_GIFT         "A Lifebinder's Gift begins to grow!"
#define EMOTE_ALLIES       "Allies of Nature have appeared!"

#define ACHIEVEMENT_KNOCK_ON_WOOD_1      RAID_MODE(3177, 3185)
#define ACHIEVEMENT_KNOCK_ON_WOOD_2      RAID_MODE(3178, 3186)
#define ACHIEVEMENT_KNOCK_ON_WOOD_3      RAID_MODE(3179, 3187)
#define ACHIEVEMENT_BACK_TO_NATURE       RAID_MODE(2982, 2983)

enum Spells
{
    // Freya
    SPELL_ATTUNED_TO_NATURE                     = 62519,
    RAID_10_SPELL_TOUCH_OF_EONAR                = 62528,
    RAID_25_SPELL_TOUCH_OF_EONAR                = 62892,
    RAID_10_SPELL_SUNBEAM                       = 62623,
    RAID_25_SPELL_SUNBEAM                       = 62872,
    SPELL_SUN_BEAM_SUMMON                       = 62450,
    SPELL_EONAR_GIFT                            = 62572,
    SPELL_NATURE_BOMB                           = 64604,
    SPELL_NATURE_BOMB_VISUAL                    = 64648,
    SPELL_SUMMON_ALLIES                         = 62678,
    SPELL_BERSERK                               = 47008,
    RAID_10_SPELL_FREYA_GROUND_TREMOR           = 62437,
    RAID_25_SPELL_FREYA_GROUND_TREMOR           = 62859,
    RAID_10_SPELL_FREYA_IRON_ROOTS              = 62283,
    RAID_25_SPELL_FREYA_IRON_ROOTS              = 62930,
    RAID_10_SPELL_FREYA_UNSTABLE_ENERGY         = 62451,
    RAID_25_SPELL_FREYA_UNSTABLE_ENERGY         = 62865,
    SPELL_STONEBARKS_ESSENCE                    = 62386,
    SPELL_IRONBRANCHS_ESSENCE                   = 62387,
    SPELL_BRIGHTLEAFS_ESSENCE                   = 62385,
    SPELL_DRAINED_OF_POWER                      = 62467,
    RAID_10_0_SPELL_FREYA_CHEST                 = 62950,
    RAID_10_1_SPELL_FREYA_CHEST                 = 62952,
    RAID_10_2_SPELL_FREYA_CHEST                 = 62953,
    RAID_10_3_SPELL_FREYA_CHEST                 = 62954,
    RAID_25_0_SPELL_FREYA_CHEST                 = 62955,
    RAID_25_1_SPELL_FREYA_CHEST                 = 62956,
    RAID_25_2_SPELL_FREYA_CHEST                 = 62957,
    RAID_25_3_SPELL_FREYA_CHEST                 = 62958,

    // Detonating Lasher
    RAID_10_SPELL_DETONATE                      = 62598,
    RAID_25_SPELL_DETONATE                      = 62937,
    SPELL_FLAME_LASH                            = 62608,

    // Ancient Conservator
    SPELL_CONSERVATORS_GRIP                     = 62532,
    RAID_10_SPELL_NATURES_FURY                  = 62589,
    RAID_25_SPELL_NATURES_FURY                  = 63571,

    // Ancient Water Spirit
    SPELL_TIDAL_WAVE                            = 62935,

    // Storm Lasher
    RAID_10_SPELL_LIGHTNING_LASH                = 62648,
    RAID_25_SPELL_LIGHTNING_LASH                = 62939,
    RAID_10_SPELL_STORMBOLT                     = 62649,
    RAID_25_SPELL_STORMBOLT                     = 62938,

    // Snaplasher
    RAID_10_SPELL_HARDENED_BARK                 = 62664,
    RAID_25_SPELL_HARDENED_BARK                 = 64191,

    // Nature Bomb
    RAID_10_SPELL_NATURE_BOMB                   = 64587,
    RAID_25_SPELL_NATURE_BOMB                   = 64650,

    // Eonars_Gift
    RAID_10_SPELL_LIFEBINDERS_GIFT              = 62584, 
    RAID_25_SPELL_LIFEBINDERS_GIFT              = 64185,
    SPELL_PHEROMONES                            = 62619,
    SPELL_EONAR_VISUAL                          = 62579,

    // Healthy Spore
    SPELL_HEALTHY_SPORE_VISUAL                  = 62538,
    SPELL_HEALTHY_SPORE_NE                      = 62591,
    SPELL_HEALTHY_SPORE_NW                      = 62582,
    SPELL_HEALTHY_SPORE_SE                      = 62592,
    SPELL_HEALTHY_SPORE_SW                      = 62593,
    SPELL_GROW                                  = 62559,
    SPELL_POTENT_PHEROMONES                     = 62541,
    SPELL_POTENT_PHEROMONES_AURA                = 64321,

    // Elder Stonebark
    RAID_10_SPELL_PETRIFIED_BARK                = 62337,
    RAID_25_SPELL_PETRIFIED_BARK                = 62933,
    SPELL_FISTS_OF_STONE                        = 62344,
    RAID_10_SPELL_GROUND_TREMOR                 = 62325,
    RAID_25_SPELL_GROUND_TREMOR                 = 62932,

    // Elder Ironbranch
    RAID_10_SPELL_IMPALE                        = 62310,
    RAID_25_SPELL_IMPALE                        = 62928,
    RAID_10_SPELL_THORN_SWARM                   = 64060,
    RAID_25_SPELL_THORN_SWARM                   = 64071,
    RAID_10_SPELL_IRON_ROOTS                    = 62438,
    RAID_25_SPELL_IRON_ROOTS                    = 62861,

    // Elder Brightleaf
    SPELL_BRIGHTLEAF_FLUX                       = 62239,
    RAID_10_SPELL_UNSTABLE_ENERGY               = 62217,
    RAID_25_SPELL_UNSTABLE_ENERGY               = 62922,
    RAID_10_SPELL_SOLAR_FLARE                   = 62240,
    RAID_25_SPELL_SOLAR_FLARE                   = 62920,
    SPELL_PHOTOSYNTHESIS                        = 62209,
    SPELL_UNSTABLE_SUN_BEAM                     = 62211,
    SPELL_UNSTABLE_SUN_BEAM_SUMMON              = 62450,
    SPELL_UNSTABLE_SUN_BEAM_VISUAL              = 62216
};

enum FreyaNpcs
{
    NPC_SUN_BEAM                                = 33170,
    NPC_DETONATING_LASHER                       = 32918,
    NPC_ANCIENT_CONSERVATOR                     = 33203,
    NPC_ANCIENT_WATER_SPIRIT                    = 33202,
    NPC_STORM_LASHER                            = 32919,
    NPC_SNAPLASHER                              = 32916,
    NPC_NATURE_BOMB                             = 34129,
    OBJECT_NATURE_BOMB                          = 194902,
    NPC_EONARS_GIFT                             = 33228,
    NPC_HEALTHY_SPORE                           = 33215,
    NPC_UNSTABLE_SUN_BEAM                       = 33050
};

enum Actions
{
    ACTION_LASHER                               = 0,
    ACTION_ELEMENTAL                            = 1,
    ACTION_ANCIENT                              = 2,
    ACTION_ELEMENTAL_DEAD                       = 3
};

Unit* pRootTarget;

struct boss_freyaAI : public BossAI
{
    boss_freyaAI(Creature *pCreature) : BossAI(pCreature, boss_freya)
    {
        pInstance = pCreature->GetInstanceData();
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
        me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true); // Death Grip jump effect
    }

    ScriptedInstance* pInstance;

    uint32 phaseTwoTimer;
    uint32 waveTimer;
    uint32 natureBombTimer;
    uint32 sunbeamTimer;
    uint32 berserkTimer;
    bool berserked;
    uint32 giftTimer;

    uint8 phase;

    uint8 spawnOrder[3];
    uint8 spawnedAdds;
    uint8 EldersCount;
    int32 uiElemTimer;
    Creature* Elemental[3];
    bool checkElementalAlive;

    bool brightleaf;
    uint32 brightleafTimer;
    bool ironbranch;
    uint32 ironbranchTimer;
    bool stonebark;
    uint32 stonebarkTimer;

    void Reset()
    {
        _Reset();

        phase = 1;
        spawnedAdds = 0;
        EldersCount = 0;
        brightleaf = false;
        ironbranch = false;
        stonebark = false;
        checkElementalAlive = true;
        randomizeSpawnOrder();   
    }

    void randomizeSpawnOrder()
    {
        //Spawn order algorithm
        spawnOrder[0] = 0; //Detonating Lasher
        spawnOrder[1] = 1; //Elemental Adds 
        spawnOrder[2] = 2; //Ancient Conservator
        
        //Swaps the entire array
        for(uint8 n = 0; n < 3; n++)
        {
            uint8 random = rand() % 2;
            uint8 temp = spawnOrder[random];
            spawnOrder[random] = spawnOrder[n];
            spawnOrder[n] = temp;
        }
    }

    void KilledUnit(Unit * /*victim*/)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
    }

    void JustDied(Unit * /*killer*/)
    {
        DoScriptText(SAY_DEATH, me);
        _JustDied();

        if (pInstance)
        {
            // Knock on Wood
            switch (EldersCount)
            {
                case 1:
                    pInstance->DoCompleteAchievement(ACHIEVEMENT_KNOCK_ON_WOOD_1);
                    break;
                case 2:
                    pInstance->DoCompleteAchievement(ACHIEVEMENT_KNOCK_ON_WOOD_2);
                    break;
                case 3:
                    pInstance->DoCompleteAchievement(ACHIEVEMENT_KNOCK_ON_WOOD_3);
                    break;
            }

            // Getting Back to Nature
            if (me->HasAura(SPELL_ATTUNED_TO_NATURE))
                if (me->GetAura(SPELL_ATTUNED_TO_NATURE, 0)->GetStackAmount() >= 25)
                    pInstance->DoCompleteAchievement(ACHIEVEMENT_BACK_TO_NATURE);
        }

        // Hard mode chest
        switch (EldersCount)
        {
            case 0:
                DoCast(RAID_MODE(RAID_10_0_SPELL_FREYA_CHEST, RAID_25_0_SPELL_FREYA_CHEST));
                break;
            case 1:
                DoCast(RAID_MODE(RAID_10_1_SPELL_FREYA_CHEST, RAID_25_1_SPELL_FREYA_CHEST));
                break;
            case 2:
                DoCast(RAID_MODE(RAID_10_2_SPELL_FREYA_CHEST, RAID_25_2_SPELL_FREYA_CHEST));
                break;
            case 3:
                DoCast(RAID_MODE(RAID_10_3_SPELL_FREYA_CHEST, RAID_25_3_SPELL_FREYA_CHEST));
                break;
        }

        instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_ACHIEVEMENT_CHECK);
    }

    void EnterCombat(Unit* /*who*/)
    {
        _EnterCombat();

        DoCast(me, RAID_MODE(RAID_10_SPELL_TOUCH_OF_EONAR, RAID_25_SPELL_TOUCH_OF_EONAR));
        for (uint32 i = 0; i < 150; ++i)
            DoCast(me, SPELL_ATTUNED_TO_NATURE);

        checkElders();

        phaseTwoTimer = 6 * 60 * 1000; // 6 minutes
        waveTimer = 1 * 60 * 1000; // 1 minute
        natureBombTimer = phaseTwoTimer + 15 * 1000; // 15 seconds after start of phase 2
        sunbeamTimer = 20 * 1000; // 20 seconds
        berserkTimer = 10 * 60 * 1000; // 10 minutes
        giftTimer = 30 * 1000; // 30 seconds
        berserked = false;

        if (EldersCount == 0)
            DoScriptText(SAY_AGGRO, me);
        else
            DoScriptText(SAY_AGGRO_WITH_ELDER, me);
    }

    void checkElders()
    {
        EldersCount = 0;
        // Freya hard mode can be triggered simply by letting the elders alive
        if(Creature* Brightleaf = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(data64_brightleaf) : 0))
        {
            if(Brightleaf->isAlive())
            {
                EldersCount++;
                DoCast(SPELL_BRIGHTLEAFS_ESSENCE);
                me->AddAura(SPELL_BRIGHTLEAFS_ESSENCE, me);
                brightleafTimer = urand(15000, 30000);
                brightleaf = true;
            }
        }

        if(Creature* Ironbranch = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(data64_ironbranch) : 0))
        {
            if(Ironbranch->isAlive())
            {
                EldersCount++;
                DoCast(SPELL_IRONBRANCHS_ESSENCE);
                me->AddAura(SPELL_IRONBRANCHS_ESSENCE, me);
                ironbranchTimer = urand(45000, 60000);
                ironbranch = true;
            }
        }

        if(Creature* Stonebark = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(data64_stonebark) : 0))
        {
            if(Stonebark->isAlive())
            {
                EldersCount++;
                DoCast(SPELL_STONEBARKS_ESSENCE);
                me->AddAura(SPELL_STONEBARKS_ESSENCE, me);
                stonebarkTimer = urand(35000, 45000);
                stonebark = true;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Elementals must be killed within 12 seconds of each other, or they will all revive and heal
        checkElementals(diff);

        if (sunbeamTimer <= diff)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                if (pTarget->isAlive())
                    DoCast(pTarget, RAID_MODE(RAID_10_SPELL_SUNBEAM, RAID_25_SPELL_SUNBEAM));
            sunbeamTimer = urand(10 * 1000, 15 * 1000); // 10-15 seconds
        } else sunbeamTimer -= diff;

        if (natureBombTimer <= diff)
        {
            DoCastAOE(SPELL_NATURE_BOMB_VISUAL);
            DoCastAOE(SPELL_NATURE_BOMB);
            natureBombTimer = urand(15 * 1000, 20 * 1000); // 15-20 seconds
        } else natureBombTimer -= diff;

        if (!berserked)
        {
            if (berserkTimer <= diff)
            {
                DoCast(me, SPELL_BERSERK, true);
                DoScriptText(SAY_BERSERK, me);
                berserked = true;
            } else berserkTimer -= diff;
        }

        if (giftTimer <= diff)
        {
            me->MonsterTextEmote(EMOTE_GIFT, 0, true);
            DoCast(SPELL_EONAR_GIFT);
            giftTimer = urand(35 * 1000, 45 * 1000);
        } else giftTimer -= diff;

        if (phase == 1)
        {
            if (phaseTwoTimer <= diff)
            {
                phase = 2;
            }
            else
            {
                phaseTwoTimer -= diff;

                // only summon allies if we haven't gone to phase 2 yet
                if (waveTimer <= diff)
                {
                    me->MonsterTextEmote(EMOTE_ALLIES, 0, true);
                    DoCast(me, SPELL_SUMMON_ALLIES);
                    spawnAdd();
                    waveTimer = 1 * 60 * 1000; // 1 minute
                } else waveTimer -= diff;
            }
        }

        // handle hardmode stuff
        if (brightleaf && brightleafTimer <= diff)
        {
            // summon three sunbeams
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, SPELL_SUN_BEAM_SUMMON);

            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, SPELL_SUN_BEAM_SUMMON);

            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, SPELL_SUN_BEAM_SUMMON);

            brightleafTimer = urand(35 * 1000, 45 * 1000);
        } else if (brightleaf) brightleafTimer -= diff;

        if (ironbranch && ironbranchTimer <= diff)
        {
            if (pRootTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                pRootTarget->CastSpell(pRootTarget,RAID_MODE(RAID_10_SPELL_IRON_ROOTS, RAID_25_SPELL_IRON_ROOTS),true);
            ironbranchTimer = urand(45 * 1000, 60 * 1000);
        } else if (ironbranch) ironbranchTimer -= diff;

        if (stonebark && stonebarkTimer <= diff)
        {
            DoCastAOE(RAID_MODE(RAID_10_SPELL_FREYA_GROUND_TREMOR, RAID_25_SPELL_FREYA_GROUND_TREMOR));
            stonebarkTimer = urand(25 * 1000, 30 * 1000);
        } else if (stonebark) stonebarkTimer -= diff;
        // end hardmode

        DoMeleeAttackIfReady();

        EnterEvadeIfOutOfCombatArea(diff);
    }

    void checkElementals(const uint32 diff)
    {
        if (checkElementalAlive)
            uiElemTimer = 0;
        else
        {
            uiElemTimer += diff;
            if (uiElemTimer > 12000)
            {
                for (uint32 i = 0; i < 3; i++)
                {
                    if (Elemental[i])
                    {
                        if (Elemental[i]->isAlive())
                            Elemental[i]->SetHealth(Elemental[i]->GetMaxHealth());
                        else
                            Elemental[i]->Respawn();
                    }
                }
                checkElementalAlive = true;
            }
            else
            {
                if (Elemental[0] && Elemental[1] && Elemental[2])
                {
                    if (Elemental[0]->isDead())
                    {
                        if (Elemental[1]->isDead())
                        {
                            if (Elemental[2]->isDead())
                            {
                                for (uint32 i = 0; i < 3; i++)
                                    Elemental[i]->ForcedDespawn(3000);
                                
                                if (Creature* Freya = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(data64_freya) : 0))
                                    Freya->AI()->DoAction(ACTION_ELEMENTAL);
                            }
                        }
                    }
                }
            }
        }
    }

    void spawnAdd()
    {
        if (spawnedAdds >= 0 && spawnedAdds <= 2)
            spawnHandler(spawnOrder[spawnedAdds]);

        spawnedAdds++;
        if(spawnedAdds > 2)
            spawnedAdds = 0;
    }

    void spawnHandler(uint8 add)
    {
        switch(add)
        {
            case 0:
            {
                DoScriptText(SAY_SUMMON_LASHERS, me);
                //Spawn 10 Detonating Lashers
                for(uint8 n = 0; n < 10; n++)
                {
                    //Make sure that they don't spawn in a pile
                    int8 randomX = -25 + rand() % 50;
                    int8 randomY = -25 + rand() % 50;
                    me->SummonCreature(NPC_DETONATING_LASHER, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1500);
                }
                break;
            }
            case 1:
            {
                DoScriptText(SAY_SUMMON_TRIO, me);
                //Make sure that they don't spawn in a pile
                int8 randomX = -25 + rand() % 50;
                int8 randomY = -25 + rand() % 50;
                Elemental[0] = me->SummonCreature(NPC_SNAPLASHER, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN);
                randomX = -25 + rand() % 50;
                randomY = -25 + rand() % 50;
                Elemental[1] = me->SummonCreature(NPC_ANCIENT_WATER_SPIRIT, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN);
                randomX = -25 + rand() % 50;
                randomY = -25 + rand() % 50;
                Elemental[2] = me->SummonCreature(NPC_STORM_LASHER, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN);
                break;
            }
            case 2: 
            {
                DoScriptText(SAY_SUMMON_CONSERVATOR, me);
                int8 randomX = -25 + rand() % 50;
                int8 randomY = -25 + rand() % 50;
                me->SummonCreature(NPC_ANCIENT_CONSERVATOR, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ()+1, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 7000);
                break;
            }
        }
    }

    void DoAction(const int32 action)
    {
        switch (action)
        {
            case ACTION_LASHER:
                for (uint32 i = 0; i < 2; ++i)
                    me->RemoveAuraFromStack(SPELL_ATTUNED_TO_NATURE, 0, AURA_REMOVE_BY_DEFAULT);
                break;
            case ACTION_ELEMENTAL:
                checkElementalAlive = true;
                for (uint32 i = 0; i < 30; ++i)
                    me->RemoveAuraFromStack(SPELL_ATTUNED_TO_NATURE, 0, AURA_REMOVE_BY_DEFAULT);
                break;
            case ACTION_ANCIENT:
                for (uint32 i = 0; i < 25; ++i)
                    me->RemoveAuraFromStack(SPELL_ATTUNED_TO_NATURE, 0, AURA_REMOVE_BY_DEFAULT);
                break;
            case ACTION_ELEMENTAL_DEAD:
                checkElementalAlive = false;
                break;
        }
    }
};

struct boss_elder_brightleafAI : public ScriptedAI
{
    boss_elder_brightleafAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    uint32 uiUnstableSunbeamTimer;
    uint32 uiSolarFlareTimer;
    uint32 uiUnstableEnergyTimer;
    uint32 uiBrightleafFluxTimer;

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_BRIGHTLEAF_AGGRO, me);
    }

    void KilledUnit(Unit *victim)
    {
        if (!(rand()%5))
             DoScriptText(RAND(SAY_BRIGHTLEAF_SLAY_1,SAY_BRIGHTLEAF_SLAY_2), me);
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_BRIGHTLEAF_DEATH, me);
    }

    void Reset()
    {
        uiUnstableSunbeamTimer = 5 * 1000;
        uiSolarFlareTimer = 10 * 1000;
        uiUnstableEnergyTimer = 20 * 1000;
        uiBrightleafFluxTimer = 0;
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim())
            return;

        if (GetClosestCreatureWithEntry(me, NPC_SUN_BEAM, 4.0f))
            DoCast(me, SPELL_PHOTOSYNTHESIS, true);

        if(uiUnstableSunbeamTimer <= diff)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                if (pTarget->isAlive())
                    me->SummonCreature(NPC_UNSTABLE_SUN_BEAM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
            uiUnstableSunbeamTimer = 8 * 1000;
        }
        else uiUnstableSunbeamTimer -= diff;

        if(uiSolarFlareTimer <= diff)
        {
            DoCast(RAID_MODE(RAID_10_SPELL_SOLAR_FLARE, RAID_25_SPELL_SOLAR_FLARE));
            uiSolarFlareTimer = urand(10 * 1000, 15 * 1000);
        } else uiSolarFlareTimer -= diff;

        if(uiUnstableEnergyTimer <= diff)
        {
            DoCast(RAID_MODE(RAID_10_SPELL_UNSTABLE_ENERGY, RAID_25_SPELL_UNSTABLE_ENERGY));
            uiUnstableEnergyTimer = 15 * 1000;
        } else uiUnstableEnergyTimer -= diff;

        if(uiBrightleafFluxTimer <= diff)
        {
            me->RemoveAurasDueToSpell(SPELL_BRIGHTLEAF_FLUX);
            for (uint32 i = 0; i < urand(1, 10); ++i)
                DoCast(me, SPELL_BRIGHTLEAF_FLUX);
            uiBrightleafFluxTimer = 4 * 1000;
        } else uiBrightleafFluxTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct creature_sun_beamAI : public Scripted_NoMovementAI
{
    creature_sun_beamAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        DoCast(RAID_MODE(RAID_10_SPELL_FREYA_UNSTABLE_ENERGY, RAID_25_SPELL_FREYA_UNSTABLE_ENERGY));
        DoCast(SPELL_UNSTABLE_SUN_BEAM_VISUAL);
    }
};

struct creature_unstable_sun_beamAI : public Scripted_NoMovementAI
{
    creature_unstable_sun_beamAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        DoCast(SPELL_UNSTABLE_SUN_BEAM);
    }
};

struct boss_elder_ironbranchAI : public ScriptedAI
{
    boss_elder_ironbranchAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 uiImpaleTimer;
    uint32 uiThornSwarmTimer;
    uint32 uiIronRootTimer;

    void Reset()
    {
        uiImpaleTimer = 15 * 1000;
        uiThornSwarmTimer = 20 * 1000;
        uiIronRootTimer = 8 * 1000;
    }

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_IRONBRANCH_AGGRO, me);
    }
    
    void KilledUnit(Unit *victim)
    {
        if (!(rand() % 5))
             DoScriptText(RAND(SAY_IRONBRANCH_SLAY_1,SAY_IRONBRANCH_SLAY_2), me);
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_IRONBRANCH_DEATH, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim())
            return;

        if(uiImpaleTimer <= diff && me->IsWithinMeleeRange(me->getVictim()))
        {
            DoCastVictim(RAID_MODE(RAID_10_SPELL_IMPALE, RAID_25_SPELL_IMPALE));
            uiImpaleTimer = urand(15 * 1000, 20 * 1000);
        } else if (me->IsWithinMeleeRange(me->getVictim())) uiImpaleTimer -= diff;

        if(uiThornSwarmTimer <= diff)
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                DoCast(pTarget, RAID_MODE(RAID_10_SPELL_THORN_SWARM, RAID_25_SPELL_THORN_SWARM));
            uiThornSwarmTimer = urand(20 * 1000, 24 * 1000);
        } else uiThornSwarmTimer -= diff;

        if(uiIronRootTimer <= diff)
        {
            pRootTarget = SelectTarget(SELECT_TARGET_RANDOM);
            if(pRootTarget && !pRootTarget->HasAura(RAID_MODE(RAID_10_SPELL_IMPALE, RAID_25_SPELL_IMPALE)))
                pRootTarget->CastSpell(me, RAID_MODE(RAID_10_SPELL_IRON_ROOTS, RAID_25_SPELL_IRON_ROOTS), false);
            uiIronRootTimer = urand(20 * 1000, 25 * 1000);
        } else uiIronRootTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct creature_iron_rootsAI : public Scripted_NoMovementAI
{
    creature_iron_rootsAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        pPlayer = pRootTarget;
    }

    ScriptedInstance* m_pInstance;
    Unit* pPlayer;

    void JustDied(Unit* victim)
    {
        if (pPlayer)
            pPlayer->RemoveAurasDueToSpell(RAID_MODE(RAID_10_SPELL_IRON_ROOTS, RAID_25_SPELL_IRON_ROOTS));
    }
};

struct boss_elder_stonebarkAI : public ScriptedAI
{
    boss_elder_stonebarkAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    uint32 uiGroundTremorTimer;
    uint32 uiFistsOfStoneTimer;
    uint32 uiPetrifiedBarkTimer;

    void Reset()
    {
        uiGroundTremorTimer = urand(5 * 1000, 10 * 1000);
        uiFistsOfStoneTimer = 25 * 1000;
        uiPetrifiedBarkTimer = 35 * 1000;
    }

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_STONEBARK_AGGRO, me);
    }
    
    void KilledUnit(Unit *victim)
    {
        if (!(rand()%5))
             DoScriptText(RAND(SAY_STONEBARK_SLAY_1,SAY_STONEBARK_SLAY_2), me);
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_STONEBARK_DEATH, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim() || me->hasUnitState(UNIT_STAT_CASTING))
            return;

        if(uiGroundTremorTimer <= diff)
        {
            DoCastVictim(RAID_MODE(RAID_10_SPELL_GROUND_TREMOR, RAID_25_SPELL_GROUND_TREMOR));
            uiGroundTremorTimer = urand(20 * 1000, 25 * 1000);
        } else uiGroundTremorTimer -= diff;

        if(uiFistsOfStoneTimer <= diff)
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_PETRIFIED_BARK, RAID_25_SPELL_PETRIFIED_BARK));
            uiFistsOfStoneTimer = 50 * 1000;
        } else uiFistsOfStoneTimer -= diff;
        
        if(uiPetrifiedBarkTimer <= diff)
        {
            DoCast(me, SPELL_FISTS_OF_STONE);
            uiPetrifiedBarkTimer = 60 * 1000;
        } else uiPetrifiedBarkTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct creature_eonars_giftAI : public Scripted_NoMovementAI
{
    creature_eonars_giftAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        uiLifebindersGiftTimer = 12 * 1000;
        fScale = 0.2;
        me->SetFloatValue(OBJECT_FIELD_SCALE_X, fScale);
        uiScaleTimer = 200;
        DoCast(me, SPELL_PHEROMONES, true);
        DoCast(me, SPELL_EONAR_VISUAL, true);
    }

    uint32 uiLifebindersGiftTimer;
    float fScale;
    uint32 uiScaleTimer;

    void UpdateAI(const uint32 diff)
    {
        if(uiLifebindersGiftTimer <= diff)
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_LIFEBINDERS_GIFT, RAID_25_SPELL_LIFEBINDERS_GIFT), true);
            uiLifebindersGiftTimer = 12 * 1000;
            me->SetFloatValue(OBJECT_FIELD_SCALE_X, 0);
            me->ForcedDespawn(1 * 1000);
        } else uiLifebindersGiftTimer -= diff;

        if(uiScaleTimer <= diff)
        {
            fScale += 0.025;
            me->SetFloatValue(OBJECT_FIELD_SCALE_X, fScale);
        } else uiScaleTimer -= diff;
    }
};

struct creature_nature_bombAI : public Scripted_NoMovementAI
{
    creature_nature_bombAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        uiExplosionTimer = 10 * 1000;
        pGo = me->SummonGameObject(OBJECT_NATURE_BOMB, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, 0, 0, 0, 0, 0);
    }

    uint32 uiExplosionTimer;
    GameObject* pGo;

    void UpdateAI(const uint32 diff)
    {
        if(uiExplosionTimer <= diff)
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_NATURE_BOMB, RAID_25_SPELL_NATURE_BOMB));
            uiExplosionTimer = 10 * 1000;
            me->ForcedDespawn(1 * 1000);
            pGo->Use(me);
        } else uiExplosionTimer -= diff;
    }
};

struct creature_detonating_lasherAI : public ScriptedAI
{
    creature_detonating_lasherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    uint32 uiFlameLashTimer;
    uint32 uiSwitchTargetTimer;

    void JustDied(Unit* victim)
    {
        DoCast(me, RAID_MODE(RAID_10_SPELL_DETONATE, RAID_25_SPELL_DETONATE));

        if(Creature* Freya = Unit::GetCreature(*me, m_pInstance ? m_pInstance->GetData64(data64_freya) : 0))
            Freya->AI()->DoAction(ACTION_LASHER);
    }

    void Reset()
    {
        uiFlameLashTimer = urand(5 * 1000, 10 * 1000);
        uiSwitchTargetTimer = urand(2 * 1000, 4 * 1000);
    }

    void updateAI(const uint32 diff)
    {
        if(!UpdateVictim())
            return;

        if(uiFlameLashTimer <= diff)
        {
            DoCastVictim(SPELL_FLAME_LASH);
            uiFlameLashTimer = urand(5 * 1000, 10 * 1000);
        }
        else uiFlameLashTimer -= diff;

        if(uiSwitchTargetTimer <= diff)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                if (pTarget->isAlive())
                    me->Attack(pTarget, true);
            uiSwitchTargetTimer = urand(2 * 1000, 4 * 1000);
        }
        else uiSwitchTargetTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct creature_ancient_conservatorAI : public ScriptedAI
{
    creature_ancient_conservatorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    uint32 uiNaturesFuryTimer;
    uint32 uiSpawnHealthySporeTimer;
    uint8 healthySporesSpawned;
    uint32 uiSpawnPauseTimer;

    void EnterCombat(Unit* pWho)
    {
        DoCast(RAND(SPELL_HEALTHY_SPORE_NE, SPELL_HEALTHY_SPORE_SE));
        DoCast(RAND(SPELL_HEALTHY_SPORE_NW, SPELL_HEALTHY_SPORE_SW));
        healthySporesSpawned += 2;
        DoCast(me, SPELL_CONSERVATORS_GRIP);
    }

    void Reset()
    {
        uiNaturesFuryTimer = 5 * 1000;
        uiSpawnHealthySporeTimer = 0;
        healthySporesSpawned = 0;
        uiSpawnPauseTimer = 20 * 1000;
    }

    void JustDied(Unit* victim)
    {
        if(Creature* Freya = Unit::GetCreature(*me, m_pInstance ? m_pInstance->GetData64(data64_freya) : 0))
            Freya->AI()->DoAction(ACTION_ANCIENT);
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim() || (me->hasUnitState(UNIT_STAT_CASTING)))
            return;

        if(uiNaturesFuryTimer <= diff)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
            //Prevent casting natures fury on a target that is already affected
            if(pTarget && !pTarget->HasAura(RAID_MODE(RAID_10_SPELL_NATURES_FURY, RAID_25_SPELL_NATURES_FURY)))
                DoCast(pTarget, RAID_MODE(RAID_10_SPELL_NATURES_FURY, RAID_25_SPELL_NATURES_FURY));
            me->AddAura(SPELL_CONSERVATORS_GRIP, me);
            uiNaturesFuryTimer = 5 * 1000;
        }
        else uiNaturesFuryTimer -= diff;

        if(uiSpawnHealthySporeTimer <= diff && healthySporesSpawned < 10)
        {
            DoCast(RAND(SPELL_HEALTHY_SPORE_NE, SPELL_HEALTHY_SPORE_SE));
            DoCast(RAND(SPELL_HEALTHY_SPORE_NW, SPELL_HEALTHY_SPORE_SW));
            healthySporesSpawned += 2;
            uiSpawnHealthySporeTimer = 2 * 1000;
        }
        else if (healthySporesSpawned < 10) uiSpawnHealthySporeTimer -= diff;

        if(uiSpawnPauseTimer <= diff)
        {
            healthySporesSpawned = 0;
            uiSpawnPauseTimer = 20 * 1000;
            uiSpawnHealthySporeTimer = 0;
        }
        else uiSpawnPauseTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct creature_healthy_sporeAI : public Scripted_NoMovementAI
{
    creature_healthy_sporeAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        DoCast(me, SPELL_HEALTHY_SPORE_VISUAL);
        DoCast(me, SPELL_POTENT_PHEROMONES);
        DoCast(me, SPELL_GROW);
        me->ForcedDespawn(20 * 1000);
    }
};

struct creature_storm_lasherAI : public ScriptedAI
{
    creature_storm_lasherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    uint32 uiLightningLashTimer;
    uint32 uiStormboltTimer;

    void Reset()
    {
        uiLightningLashTimer = 4 * 1000;
        uiStormboltTimer = 15 * 1000;
    }

    void JustDied(Unit* victim)
    {
        if(Creature* Freya = Unit::GetCreature(*me, m_pInstance ? m_pInstance->GetData64(data64_freya) : 0))
            Freya->AI()->DoAction(ACTION_ELEMENTAL_DEAD);
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim() || (me->hasUnitState(UNIT_STAT_CASTING)))
            return;
            
        if(uiLightningLashTimer <= diff)
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                DoCast(pTarget, RAID_MODE(RAID_10_SPELL_LIGHTNING_LASH, RAID_25_SPELL_LIGHTNING_LASH));
            uiLightningLashTimer = urand(3 * 1000, 6 * 1000);
        }
        else uiLightningLashTimer -= diff;

        if(uiStormboltTimer <= diff)
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                DoCast(pTarget, RAID_MODE(RAID_10_SPELL_STORMBOLT, RAID_25_SPELL_STORMBOLT));
            uiStormboltTimer = 15 * 1000;
        }
        else uiStormboltTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct creature_snaplasherAI : public ScriptedAI
{
    creature_snaplasherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        DoCast(me, RAID_MODE(RAID_10_SPELL_HARDENED_BARK, RAID_25_SPELL_HARDENED_BARK));
    }

    ScriptedInstance* m_pInstance;

    void JustDied(Unit* victim)
    {
        if(Creature* Freya = Unit::GetCreature(*me, m_pInstance ? m_pInstance->GetData64(data64_freya) : 0))
            Freya->AI()->DoAction(ACTION_ELEMENTAL_DEAD);
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

struct creature_ancient_water_spiritAI : public ScriptedAI
{
    creature_ancient_water_spiritAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    uint32 uiTidalWaveTimer;

    void Reset()
    {
        uiTidalWaveTimer = 10 * 1000;
    }

    void JustDied(Unit* victim)
    {
        if(Creature* Freya = Unit::GetCreature(*me, m_pInstance ? m_pInstance->GetData64(data64_freya) : 0))
            Freya->AI()->DoAction(ACTION_ELEMENTAL_DEAD);
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim())
            return;

        if(uiTidalWaveTimer <= diff)
        {
            DoCastVictim(SPELL_TIDAL_WAVE);
            uiTidalWaveTimer = 15 * 1000;
        }
        else uiTidalWaveTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

void AddSC_boss_freya()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_freya";
    newscript->GetAI = &get_ai<boss_freyaAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_brightleaf";
    newscript->GetAI = &get_ai<boss_elder_brightleafAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_sun_beam";
    newscript->GetAI = &get_ai<creature_sun_beamAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_unstable_sun_beam";
    newscript->GetAI = &get_ai<creature_unstable_sun_beamAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_ironbranch";
    newscript->GetAI = &get_ai<boss_elder_ironbranchAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_iron_roots";
    newscript->GetAI = &get_ai<creature_iron_rootsAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_stonebark";
    newscript->GetAI = &get_ai<boss_elder_stonebarkAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_eonars_gift";
    newscript->GetAI = &get_ai<creature_eonars_giftAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_nature_bomb";
    newscript->GetAI = &get_ai<creature_nature_bombAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_detonating_lasher";
    newscript->GetAI = &get_ai<creature_detonating_lasherAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_ancient_conservator";
    newscript->GetAI = &get_ai<creature_ancient_conservatorAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_healthy_spore";
    newscript->GetAI = &get_ai<creature_healthy_sporeAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_storm_lasher";
    newscript->GetAI = &get_ai<creature_storm_lasherAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_snaplasher";
    newscript->GetAI = &get_ai<creature_snaplasherAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_ancient_water_spirit";
    newscript->GetAI = &get_ai<creature_ancient_water_spiritAI>;
    newscript->RegisterSelf();
}
