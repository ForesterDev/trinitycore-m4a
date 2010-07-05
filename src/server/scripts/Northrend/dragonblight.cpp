/* Copyright (C) 2008 - 2010 Trinity <http://www.trinitycore.org/>
 * Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Dragonblight
SD%Complete: 100
SDComment:
SDCategory: Dragonblight
EndScriptData */

/* ContentData
npc_alexstrasza_wr_gate
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum eEnums
{
    QUEST_RETURN_TO_AG_A    = 12499,
    QUEST_RETURN_TO_AG_H    = 12500,
    MOVIE_ID_GATES          = 14
};

#define GOSSIP_ITEM_WHAT_HAPPENED   "Alexstrasza, can you show me what happened here?"

bool GossipHello_npc_alexstrasza_wr_gate(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestRewardStatus(QUEST_RETURN_TO_AG_A) || pPlayer->GetQuestRewardStatus(QUEST_RETURN_TO_AG_H))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WHAT_HAPPENED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_alexstrasza_wr_gate(Player* pPlayer, Creature* /*pCreature*/, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->SendMovieStart(MOVIE_ID_GATES);
    }

    return true;
}

/*######
## npc_inquisitor_hallard. Quest 12321
######*/


enum eInquisitor
{    
    NPC_GODFREY                 = 27577,
    SPELL_HOLY_FIRE             = 39323,

    SAY_WP_0                    = -1800014,
    SAY_WP_1                    = -1800015,
    SAY_WP_2                    = -1800016,
    SAY_WP_3                    = -1800017,
    SAY_WP_4                    = -1800018,
    SAY_WP_5                    = -1800019,
    SAY_WP_6                    = -1800020,
    SAY_WP_7                    = -1800021,
    SAY_WP_8                    = -1800022,
    SAY_WP_9                    = -1800023,
    SAY_WP_10                   = -1800024,
    SAY_WP_11                   = -1800025,
    SAY_WP_12                   = -1800026,
    SAY_WP_13                   = -1800027,
    SAY_WP_14                   = -1800028,
    SAY_WP_15                   = -1800029,
    SAY_WP_16                   = -1800030,
    SAY_WP_17                   = -1800031,
    SAY_WP_18                   = -1800032,
    SAY_WP_19                   = -1800033,
    SAY_WP_20                   = -1800034,
    SAY_WP_21                   = -1800035,
    SAY_WP_22                   = -1800036,
    SAY_WP_23                   = -1800037,
    SAY_WP_24                   = -1800038,
    SAY_WP_25                   = -1800039,
    SAY_WP_26                   = -1800040,
    SAY_WP_27                   = -1800041
};

#define QUEST_A_RIGHTEOUS_SERMON     12321

struct npc_inquisitor_hallardAI : public npc_escortAI
{    
    npc_inquisitor_hallardAI(Creature* pCreature) : npc_escortAI(pCreature) { }

    bool Completed;

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;
        Creature* Godfrey = me->FindNearestCreature(NPC_GODFREY, 50, true);
        if (!Godfrey)
            return;  
        switch (i)
        {
            case 1:                
                DoScriptText(SAY_WP_1, me, Godfrey);
                me->SetUInt64Value(UNIT_FIELD_TARGET, Godfrey->GetGUID());
                me->HandleEmoteCommand(5);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);                
                break;
            case 2:
                Godfrey->HandleEmoteCommand(434);
                DoScriptText(SAY_WP_2, me, Godfrey);
                me->HandleEmoteCommand(15);
                break;
            case 3:                
                DoScriptText(SAY_WP_3, me, Godfrey);
                me->HandleEmoteCommand(1);
                break;
            case 4:
                DoScriptText(SAY_WP_4, Godfrey);
                break;
            case 5:
                DoScriptText(SAY_WP_5, Godfrey);
                break;
            case 6:
                DoScriptText(SAY_WP_6, Godfrey);
                break;
            case 7:
                DoScriptText(SAY_WP_7, me, Godfrey);
                me->HandleEmoteCommand(1);
                break;
            case 8:
                DoScriptText(SAY_WP_8, me, Godfrey);
                me->HandleEmoteCommand(16);
                break;
            case 9:
                DoScriptText(SAY_WP_9, me, Godfrey);                
                me->HandleEmoteCommand(5);
                break;
            case 10:
                DoScriptText(SAY_WP_10, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 11:
                Godfrey->HandleEmoteCommand(434);
                DoScriptText(SAY_WP_11, Godfrey);
                break;
            case 12:
                DoScriptText(SAY_WP_12, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 13:
                DoScriptText(SAY_WP_13, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 14:
                Godfrey->HandleEmoteCommand(434);
                DoScriptText(SAY_WP_14, Godfrey);
                break;
            case 15:
                DoScriptText(SAY_WP_15, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 16:
                DoScriptText(SAY_WP_16, me, Godfrey);
                break;
            case 17:
                DoScriptText(SAY_WP_17, me, Godfrey);
                break;
            case 18:
                DoScriptText(SAY_WP_18, Godfrey);
                break;
            case 19:
                DoScriptText(SAY_WP_19, me, Godfrey);
                break;
            case 20:
                DoScriptText(SAY_WP_20, Godfrey);
                break;
            case 21:
                DoScriptText(SAY_WP_21, Godfrey);
                break;
            case 22:
                DoScriptText(SAY_WP_22, me, Godfrey);
                break;
            case 23:
                DoScriptText(SAY_WP_23, Godfrey);
                break;
            case 24:
                DoScriptText(SAY_WP_24, Godfrey);
                break;
            case 25:
                DoScriptText(SAY_WP_25, me, Godfrey);
                break;
            case 26:
                DoScriptText(SAY_WP_26, me);
                me->SetUInt64Value(UNIT_FIELD_TARGET, pPlayer->GetGUID());
                break;
            case 27:
                DoScriptText(SAY_WP_27, me, Godfrey);
                me->SetUInt64Value(UNIT_FIELD_TARGET, Godfrey->GetGUID());
                Completed = true;                
                if (pPlayer)
                    pPlayer->GroupEventHappens(QUEST_A_RIGHTEOUS_SERMON, me);
                break;                          
        }
    }

    void Reset()
    {  
        Completed = false;
    }    

    void UpdateAI(const uint32 diff)
    {          
        npc_escortAI::UpdateAI(diff);             
    }
};

bool QuestAccept_npc_inquisitor_hallard(Player* pPlayer, Creature* pCreature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_A_RIGHTEOUS_SERMON)
    {        
        DoScriptText(SAY_WP_0, pCreature, pPlayer);
        if (npc_escortAI* pEscortAI = CAST_AI(npc_inquisitor_hallardAI, pCreature->AI()))
        {
            pEscortAI->Start(true, false, pPlayer->GetGUID(), 0, true);
            pCreature->GetMotionMaster()->MovePoint(0, 3801.543, -679.350, 213.75);            
        }
    }
    return true;
}

CreatureAI* GetAI_npc_inquisitor_hallard(Creature* pCreature)
{
    return new npc_inquisitor_hallardAI(pCreature);
}

#define SPELL_SEEDS_OF_NATURES_WRATH 49587
#define QUEST_THAT_WHICH_CREATES_CAN_ALSO_DESTROY 12459

#define NPC_WEAKENED_REANIMATED_FROST_WYRM 27821
#define NPC_WEAKENED_TURGID_THE_VILE 27809
#define NPC_WEAKENED_OVERSEER_DEATHGAZE 27807

struct npc_reanimated_frost_wormAI : public ScriptedAI
{
    npc_reanimated_frost_wormAI(Creature *c) : ScriptedAI(c) {}

    void SpellHit(Unit *hitter, const SpellEntry *spell)
    {
        if ((spell->Id == SPELL_SEEDS_OF_NATURES_WRATH) &&
            (hitter->GetTypeId() == TYPEID_PLAYER) &&
            (CAST_PLR(hitter)->IsActiveQuest(QUEST_THAT_WHICH_CREATES_CAN_ALSO_DESTROY)))
        {
            me->UpdateEntry(NPC_WEAKENED_REANIMATED_FROST_WYRM);
        }
    }
};

struct npc_turgid_the_vileAI : public ScriptedAI
{
    npc_turgid_the_vileAI(Creature *c) : ScriptedAI(c) {}

    void SpellHit(Unit *hitter, const SpellEntry *spell)
    {
        if ((spell->Id == SPELL_SEEDS_OF_NATURES_WRATH) &&
            (hitter->GetTypeId() == TYPEID_PLAYER) &&
            (CAST_PLR(hitter)->IsActiveQuest(QUEST_THAT_WHICH_CREATES_CAN_ALSO_DESTROY)))
        {
            me->UpdateEntry(NPC_WEAKENED_TURGID_THE_VILE);
        }
    }
};

struct npc_overseer_deathgazeAI : public ScriptedAI
{
    npc_overseer_deathgazeAI(Creature *c) : ScriptedAI(c) {}

    void SpellHit(Unit *hitter, const SpellEntry *spell)
    {
        if ((spell->Id == SPELL_SEEDS_OF_NATURES_WRATH) &&
            (hitter->GetTypeId() == TYPEID_PLAYER) &&
            (CAST_PLR(hitter)->IsActiveQuest(QUEST_THAT_WHICH_CREATES_CAN_ALSO_DESTROY)))
        {
            me->UpdateEntry(NPC_WEAKENED_OVERSEER_DEATHGAZE);
        }
    }
};

void AddSC_dragonblight()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_alexstrasza_wr_gate";
    newscript->pGossipHello = &GossipHello_npc_alexstrasza_wr_gate;
    newscript->pGossipSelect = &GossipSelect_npc_alexstrasza_wr_gate;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_inquisitor_hallard";
    newscript->GetAI = &GetAI_npc_inquisitor_hallard;
    newscript->pQuestAccept = &QuestAccept_npc_inquisitor_hallard;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_reanimated_frost_worm";
    newscript->GetAI = &get_ai<npc_reanimated_frost_wormAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_turgid_the_vile";
    newscript->GetAI = &get_ai<npc_turgid_the_vileAI>;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_overseer_deathgaze";
    newscript->GetAI = &get_ai<npc_overseer_deathgazeAI>;
    newscript->RegisterSelf();
}
