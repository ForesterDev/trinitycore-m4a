#include <string>
#include "ScriptedInstance.h"

struct instance_ulduar
    : public ScriptedInstance
{
    instance_ulduar(Map *pMap);

    uint32 colossi;
    std::string m_strInstData;
    uint8  flag;

    uint64 uiLeviathanGUID;
    uint64 uiIgnisGUID;
    uint64 uiRazorscaleGUID;
    uint64 uiXT002GUID;
    uint64 uiAssemblyGUIDs[3];
    uint64 uiKologarnGUID;
    uint64 uiAuriayaGUID;
    uint64 uiMimironGUID;
    uint64 uiHodirGUID;
    uint64 uiThorimGUID;
    uint64 uiFreyaGUID;
    uint64 uiStonebarkGUID;
    uint64 uiIronbranchGUID;
    uint64 uiBrightleafGUID;
    uint64 uiVezaxGUID;
    uint64 uiYoggSaronGUID;
    uint64 uiAlgalonGUID;
    uint64 uiLeviathanDoor[7];
    uint64 uiLeviathanGateGUID;

    uint64 uiKologarnChestGUID;
    uint64 uiThorimChestGUID;
    uint64 uiHodirChestGUID;
    uint64 uiFreyaChestGUID;
    bool razorscale_state;

    void Initialize();

    void OnCreatureCreate(Creature *pCreature, bool add);

    void OnGameObjectCreate(GameObject *pGO, bool add);

    void ProcessEvent(GameObject *pGO, uint32 uiEventId);

    void SetData(uint32 DataId, uint32 Value);

    uint64 GetData64(uint32 DataId);

    uint32 GetData(uint32 DataId);

    std::string GetSaveData();

    void Load(const char *strIn);

    bool SetBossState(uint32 id, EncounterState state);
};
