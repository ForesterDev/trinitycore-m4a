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

#include "ScriptedEscortAI.h"
#include "ScriptPCH.h"
#include "instance_ulduar.hpp"
#include "ulduar.h"

enum eGameObjects
{
    GO_KOLOGARN_CHEST_HERO  = 195047,
    GO_KOLOGARN_CHEST       = 195046,
    GO_THORIM_CHEST_HERO    = 194315,
    GO_THORIM_CHEST         = 194314,
    GO_HODIR_CHEST_HERO     = 194308,
    GO_HODIR_CHEST          = 194307,
    GO_FREYA_CHEST_HERO     = 194325,
    GO_FREYA_CHEST          = 194324,
    GO_LEVIATHAN_DOOR       = 194905,
    GO_LEVIATHAN_GATE       = 194630
};

instance_ulduar::instance_ulduar(Map *pMap)
    : ScriptedInstance(pMap)
{
    SetBossNumber(num_bosses);
    Initialize();
}

void instance_ulduar::Initialize()
{
    colossi               = 0;
    uiIgnisGUID           = 0;
    uiRazorscaleGUID      = 0;
    uiXT002GUID           = 0;
    uiKologarnGUID        = 0;
    uiAuriayaGUID         = 0;
    uiMimironGUID         = 0;
    uiHodirGUID           = 0;
    uiThorimGUID          = 0;
    uiFreyaGUID           = 0;
    uiStonebarkGUID       = 0;
    uiIronbranchGUID      = 0;
    uiBrightleafGUID      = 0;
    uiVezaxGUID           = 0;
    uiYoggSaronGUID       = 0;
    uiAlgalonGUID         = 0;
    uiKologarnChestGUID   = 0;
    uiKologarnChestGUID   = 0;
    uiHodirChestGUID      = 0;
    uiFreyaChestGUID      = 0;
    uiLeviathanGateGUID   = 0;
    flag                  = 0;

    memset(&uiAssemblyGUIDs, 0, sizeof(uiAssemblyGUIDs));
    memset(&uiLeviathanDoor, 0, sizeof(uiLeviathanDoor));
    razorscale_state = false;
}

void instance_ulduar::OnCreatureCreate(Creature *pCreature, bool)
{
    switch(pCreature->GetEntry())
    {
        case NPC_LEVIATHAN:
            uiLeviathanGUID = pCreature->GetGUID();             
            break;
        case NPC_IGNIS:
            uiIgnisGUID = pCreature->GetGUID();
            break;
        case NPC_RAZORSCALE:
            uiRazorscaleGUID = pCreature->GetGUID();
            break;
        case NPC_XT002:
            uiXT002GUID = pCreature->GetGUID();
            break;

        // Assembly of Iron
        case NPC_STEELBREAKER:
            uiAssemblyGUIDs[0] = pCreature->GetGUID();
            break;
        case NPC_MOLGEIM:
            uiAssemblyGUIDs[1] = pCreature->GetGUID();
            break;
        case NPC_BRUNDIR:
            uiAssemblyGUIDs[2] = pCreature->GetGUID();
            break;

        case NPC_KOLOGARN:
            uiKologarnGUID = pCreature->GetGUID();
            break;
        case NPC_AURIAYA:
            uiAuriayaGUID = pCreature->GetGUID();
            break;
        case NPC_MIMIRON:
            uiMimironGUID = pCreature->GetGUID();
            break;
        case NPC_HODIR:
            uiHodirGUID = pCreature->GetGUID();
            break;
        case NPC_THORIM:
            uiThorimGUID = pCreature->GetGUID();
            break;
        case NPC_FREYA:
            uiFreyaGUID = pCreature->GetGUID();
            break;
        case NPC_STONEBARK:
            uiStonebarkGUID = pCreature->GetGUID();
            break;
        case NPC_IRONBRANCH:
            uiIronbranchGUID = pCreature->GetGUID();
            break;
        case NPC_BRIGHTLEAF:
            uiBrightleafGUID = pCreature->GetGUID();
            break;
        case NPC_VEZAX:
            uiVezaxGUID = pCreature->GetGUID();
            break;
        case NPC_YOGGSARON:
            uiYoggSaronGUID = pCreature->GetGUID();
            break;
        case NPC_ALGALON:
            uiAlgalonGUID = pCreature->GetGUID();
            break;
    }

}

void instance_ulduar::OnGameObjectCreate(GameObject *pGO, bool add)
{
    switch(pGO->GetEntry())
    {
        case GO_KOLOGARN_CHEST_HERO:
        case GO_KOLOGARN_CHEST:
            uiKologarnChestGUID  = add ? pGO->GetGUID() : NULL;
            break;
        case GO_THORIM_CHEST_HERO:
        case GO_THORIM_CHEST:
            uiThorimChestGUID = add ? pGO->GetGUID() : NULL;
            break;
        case GO_HODIR_CHEST_HERO:
        case GO_HODIR_CHEST:
            uiHodirChestGUID = add ? pGO->GetGUID() : NULL;
            break;
        case GO_FREYA_CHEST_HERO:
        case GO_FREYA_CHEST:
            uiFreyaChestGUID = add ? pGO->GetGUID() : NULL;
            break;
        case GO_LEVIATHAN_DOOR:
            uiLeviathanDoor[flag] = pGO->GetGUID();
            HandleGameObject(NULL, true, pGO);
            flag++;
            if (flag == 7)
                flag =0;
            break;
        case GO_LEVIATHAN_GATE:                
            uiLeviathanGateGUID = add ? pGO->GetGUID() : NULL;
            HandleGameObject(NULL, false, pGO); 
            if (2 <= colossi)
                pGO->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
            break;             
    }
}

void instance_ulduar::ProcessEvent(GameObject *pGO, uint32 uiEventId)
{
    // Flame Leviathan's Tower Event triggers
   Creature* pFlameLeviathan = instance->GetCreature(uiLeviathanGUID);

    if (pFlameLeviathan && pFlameLeviathan->isAlive()) //No leviathan, no event triggering ;)
        switch(uiEventId)
        {
            case EVENT_TOWER_OF_STORM_DESTROYED:
                    //pGO->GetInstanceData()->SetData(DATA_TOWER_STORMS,DESTROYED);
                pFlameLeviathan->AI()->DoAction(1);                    
                break;
            case EVENT_TOWER_OF_FROST_DESTROYED:
                pFlameLeviathan->AI()->DoAction(2);
                break;
            case EVENT_TOWER_OF_FLAMES_DESTROYED:
                pFlameLeviathan->AI()->DoAction(3);
                break;
            case EVENT_TOWER_OF_LIFE_DESTROYED:
                pFlameLeviathan->AI()->DoAction(4);
                break;
        }
}

void instance_ulduar::SetData(uint32 DataId, uint32 Value)
{
    switch (DataId)
    {
        case DATA_COLOSSUS:
            if (colossi != Value)
            {
                colossi = Value;
                if (colossi == 2)
                {
                    if (Creature* pBoss = instance->GetCreature(uiLeviathanGUID))
                        pBoss->AI()->DoAction(10);
                    if (GameObject* pGate = instance->GetGameObject(uiLeviathanGateGUID))
                        pGate->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);                                                               
                }

                SaveToDB();
            }
            break;            
        default:
            break;
    }
}

uint64 instance_ulduar::GetData64(uint32 DataId)
{
    switch (DataId)
    {
        case data64_leviathan:
            return uiLeviathanGUID;
        case data64_ignis:
            return uiIgnisGUID;
        case data64_razorscale:
            return uiRazorscaleGUID;
        case data64_xt002:
            return uiXT002GUID;
        case data64_kologarn:
            return uiKologarnGUID;
        case data64_auriaya:
            return uiAuriayaGUID;
        case data64_mimiron:
            return uiMimironGUID;
        case data64_hodir:
            return uiMimironGUID;
        case data64_thorim:
            return uiThorimGUID;
        case data64_freya:
            return uiFreyaGUID;
        case data64_stonebark:
            return uiStonebarkGUID;
        case data64_ironbranch:
            return uiIronbranchGUID;
        case data64_brightleaf:
            return uiBrightleafGUID;
        case data64_vezax:
            return uiVezaxGUID;
        case data64_yoggsaron:
            return uiYoggSaronGUID;
        case data64_algalon:
            return uiAlgalonGUID;

        // Assembly of Iron
        case DATA_STEELBREAKER:         return uiAssemblyGUIDs[0];
        case DATA_MOLGEIM:              return uiAssemblyGUIDs[1];
        case DATA_BRUNDIR:              return uiAssemblyGUIDs[2];
    }

    return 0;
}

uint32 instance_ulduar::GetData(uint32 DataId)
{
    switch (DataId)
    {
    case DATA_COLOSSUS:
        return colossi;
    }

    return 0;
}

std::string instance_ulduar::GetSaveData()
{
    OUT_SAVE_INST_DATA;

    std::ostringstream saveStream;
    saveStream << "U U " << GetBossSaveData() << ' ' << colossi;

    m_strInstData = saveStream.str();

    OUT_SAVE_INST_DATA_COMPLETE;
    return m_strInstData;
}

void instance_ulduar::Load(const char *strIn)
{
    if (!strIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(strIn);

    char dataHead1, dataHead2;

    std::istringstream loadStream(strIn);
    loadStream >> dataHead1 >> dataHead2;

    if (dataHead1 == 'U' && dataHead2 == 'U')
        LoadBossState(loadStream) >> colossi;
    OUT_LOAD_INST_DATA_COMPLETE;
}

bool instance_ulduar::SetBossState(uint32 id, EncounterState state)
{
    if (InstanceData::SetBossState(id, state))
    {
        switch (id)
        {
        case boss_leviathan:
            if (state == IN_PROGRESS)
            {
                for (uint8 uiI = 0; uiI < 7; ++uiI)
                    HandleGameObject(uiLeviathanDoor[uiI],false);
            }
            else
            {
                for (uint8 uiI = 0; uiI < 7; ++uiI)
                    HandleGameObject(uiLeviathanDoor[uiI],true);
            }
            break;
        case boss_kologarn:
            if (state == DONE)
                if (GameObject* pGO = instance->GetGameObject(uiKologarnChestGUID))
                    pGO->SetRespawnTime(pGO->GetRespawnDelay());
            break;
        case boss_hodir:
            if (state == DONE)
                if (GameObject* pGO = instance->GetGameObject(uiHodirChestGUID))
                    pGO->SetRespawnTime(pGO->GetRespawnDelay());
            break;
        case boss_thorim:
            if (state == DONE)
                if (GameObject* pGO = instance->GetGameObject(uiThorimChestGUID))
                    pGO->SetRespawnTime(pGO->GetRespawnDelay());
            break;
        case boss_freya:
            if (state == DONE)
                if (GameObject* pGO = instance->GetGameObject(uiFreyaChestGUID))
                    pGO->SetRespawnTime(pGO->GetRespawnDelay());
            break;
        }
        return true;
    }
    else
        return false;
}

void AddSC_instance_ulduar()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_ulduar";
    newscript->GetInstanceData = &get_instance_data<instance_ulduar>;
    newscript->RegisterSelf();
}
