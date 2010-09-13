#pragma once

#include <utility>
#include <vector>
#include "Define.h"
#include "InstanceScript.h"

class instance_ulduar
    : public InstanceScript
{
private:
    typedef std::vector<Creature *> Ominous_clouds;

public:
    typedef Ominous_clouds::iterator Ominous_clouds_iterator;

    instance_ulduar(Map *pMap);

    void OnGameObjectCreate(GameObject *pGo, bool add);

    void OnCreatureCreate(Creature *pCreature, bool add);

    uint64 GetData64(uint32 id);

    void SetData(uint32 id, uint32 value);

    bool SetBossState(uint32 id, EncounterState state);

    void connect_prison()
    {
        set_player_zone_changed_handler(Prison_handler(this));
    }

    void disconnect_prison()
    {
        set_player_zone_changed_handler(nullptr);
    }

    Creature *sara()
    {
        return sara_;
    }

    const Creature *sara() const
    {
        return sara_;
    }

    Creature *yoggsaron()
    {
        return yoggsaron_;
    }

    const Creature *yoggsaron() const
    {
        return yoggsaron_;
    }

    std::pair<Ominous_clouds_iterator, Ominous_clouds_iterator> ominous_clouds()
    {
        return std::make_pair(ominous_clouds_.begin(), ominous_clouds_.end());
    }

    Creature *ys_mimiron()
    {
        return ys_mimiron_;
    }

    const Creature *ys_mimiron() const
    {
        return ys_mimiron_;
    }

    Creature *ys_thorim()
    {
        return ys_thorim_;
    }

    const Creature *ys_thorim() const
    {
        return ys_thorim_;
    }

    GameObject *yoggsaron_door()
    {
        return yoggsaron_door_;
    }

    const GameObject *yoggsaron_door() const
    {
        return yoggsaron_door_;
    }

private:
    struct Prison_handler
    {
        explicit Prison_handler(instance_ulduar *i)
            : i(i)
        {
        }

        void operator()(Player &p);

        instance_ulduar *i;
    };

    void CheckKeepersState();

    uint64 uiLeviathan;
    uint64 uiNorgannon;
    uint64 uiIgnis;
    uint64 uiRazorscale;
    uint64 uiExpCommander;
    uint64 uiXT002;
    uint64 uiSteelbreaker;
    uint64 uiMolgeim;
    uint64 uiBrundir;
    uint64 uiKologarn;
    uint64 uiRightArm;
    uint64 uiLeftArm;
    uint64 uiKologarnBridge;
    uint64 uiAuriaya;
    uint64 uiBrightleaf;
    uint64 uiIronbranch;
    uint64 uiStonebark;
    uint64 uiFreya;
    uint64 uiThorim;
    uint64 uiRunicColossus;
    uint64 uiRuneGiant;
    uint64 uiMimiron;
    uint64 uiLeviathanMKII;
    uint64 uiVX001;
    uint64 uiAerialUnit;
    uint64 uiMagneticCore;
    uint64 KeepersGateGUID;
    uint64 uiVezax;
    uint64 uiFreyaImage;
    uint64 uiThorimImage;
    uint64 uiMimironImage;
    uint64 uiHodirImage;
    uint64 uiFreyaYS;
    uint64 uiThorimYS;
    uint64 uiMimironYS;
    uint64 uiHodirYS;
        
    GameObject* pLeviathanDoor, *HodirRareChest, *pRunicDoor, *pStoneDoor, *pThorimLever, *MimironTram, *MimironElevator;
    Creature *sara_;
    Creature *yoggsaron_;
    Ominous_clouds ominous_clouds_;
    Creature *ys_mimiron_;
    Creature *ys_thorim_;
    GameObject *yoggsaron_door_;
};
