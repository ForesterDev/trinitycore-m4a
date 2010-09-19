/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_GENERIC which cannot be included in AI script file
 * of creature using it or can't be bound to any player class.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_gen_"
 */

#include "ScriptPCH.h"

enum NPCEntries
{
    NPC_DOOMGUARD                                = 11859,
    NPC_INFERNAL                                 = 89,
    NPC_IMP                                      = 416,
};

class spell_gen_pet_summoned : public SpellScriptLoader
{
public:
    spell_gen_pet_summoned() : SpellScriptLoader("spell_gen_pet_summoned") { }

    class spell_gen_pet_summonedSpellScript : public SpellScript
    {
        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Unit *caster = GetCaster();
            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            Player* plr = caster->ToPlayer();
            if (plr && plr->GetLastPetNumber())
            {
                PetType NewPetType = (plr->getClass() == CLASS_HUNTER) ? HUNTER_PET : SUMMON_PET;
                if (Pet* NewPet = new Pet(plr, NewPetType))
                {
                    if (NewPet->LoadPetFromDB(plr, 0, plr->GetLastPetNumber(), true))
                    {
                        // revive the pet if it is dead
                        if (NewPet->getDeathState() == DEAD)
                            NewPet->setDeathState(ALIVE);

                        NewPet->SetFullHealth();
                        NewPet->SetPower(NewPet->getPowerType(),NewPet->GetMaxPower(NewPet->getPowerType()));

                        switch (NewPet->GetEntry())
                        {
                            case NPC_DOOMGUARD:
                            case NPC_INFERNAL:
                                NewPet->SetEntry(NPC_IMP);
                                break;
                            default:
                                break;
                        }
                    }
                    else
                        delete NewPet;
                }
            }
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_gen_pet_summonedSpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_pet_summonedSpellScript();
    }
};

namespace
{
    struct Purge_vehicle_control
        : SpellScriptLoader
    {
        struct Purge_vehicle_control_SS
            : SpellScript
        {
            typedef Purge_vehicle_control_SS Myt;

            void Register()
            {
                OnEffect += SpellEffectFn(Myt::effect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }

            void effect(SpellEffIndex)
            {
                if (auto v = GetCaster()->GetVehicleBase())
                {
                    auto &auras = v->GetAppliedAuras();
                    for (auto it = auras.begin(); it != auras.end(); )
                        if (it->second->IsPositive())
                            v->RemoveAura(it);
                        else
                            ++it;
                }
            }
        };

        Purge_vehicle_control()
            : SpellScriptLoader("spell_gen_purge_vehicle_control")
        {
        }

        SpellScript *GetSpellScript() const
        {
            return new Purge_vehicle_control_SS;
        }
    };
}

class spell_gen_remove_flight_auras : public SpellScriptLoader
{
public:
    spell_gen_remove_flight_auras() : SpellScriptLoader("spell_gen_remove_flight_auras") {}

    class spell_gen_remove_flight_auras_SpellScript : public SpellScript
    {
        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Unit *target = GetHitUnit();
            if (!target)
                return;
            target->RemoveAurasByType(SPELL_AURA_FLY);
            target->RemoveAurasByType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED);
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_gen_remove_flight_auras_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_gen_remove_flight_auras_SpellScript();
    }
};

class spell_creature_permanent_feign_death : public SpellScriptLoader
{
    public:
        spell_creature_permanent_feign_death() : SpellScriptLoader("spell_creature_permanent_feign_death") { }

        class spell_creature_permanent_feign_deathAuraScript : public AuraScript
        {
            void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraApplication const * aurApp, AuraEffectHandleModes /*mode*/)
            {
                Unit* pTarget = aurApp->GetTarget();
                if (!pTarget)
                    return;

                pTarget->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                pTarget->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_creature_permanent_feign_deathAuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

    AuraScript *GetAuraScript() const
    {
        return new spell_creature_permanent_feign_deathAuraScript();
    }
};

enum PvPTrinketTriggeredSpells
{
    SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER         = 72752,
    SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER_WOTF    = 72757,
};
class spell_pvp_trinket_wotf_shared_cd : public SpellScriptLoader
{
public:
    spell_pvp_trinket_wotf_shared_cd() : SpellScriptLoader("spell_pvp_trinket_wotf_shared_cd") {}

    class spell_pvp_trinket_wotf_shared_cd_SpellScript : public SpellScript
    {
        bool Validate(SpellEntry const * /*spellEntry*/)
        {
            if (!sSpellStore.LookupEntry(SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER))
                return false;
            if (!sSpellStore.LookupEntry(SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER_WOTF))
                return false;
            return true;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Player* pCaster = GetCaster()->ToPlayer();
            if (!pCaster)
                return;
            const SpellEntry* m_spellInfo = GetSpellInfo();

            pCaster->AddSpellCooldown(m_spellInfo->Id, NULL, time(NULL) + GetSpellRecoveryTime(sSpellStore.LookupEntry(SPELL_WILL_OF_THE_FORSAKEN_COOLDOWN_TRIGGER)) / IN_MILLISECONDS);
            WorldPacket data(SMSG_SPELL_COOLDOWN, 8+1+4);
            data << uint64(pCaster->GetGUID());
            data << uint8(0);
            data << uint32(m_spellInfo->Id);
            data << uint32(0);
            pCaster->GetSession()->SendPacket(&data);
        }

        void Register()
        {
            OnEffect += SpellEffectFn(spell_pvp_trinket_wotf_shared_cd_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pvp_trinket_wotf_shared_cd_SpellScript();
    }
};

namespace
{
    struct Wintergarde_gryphon_commander
        : SpellScriptLoader
    {
        struct Wintergarde_gryphon_commander_AS
            : AuraScript
        {
            typedef Wintergarde_gryphon_commander_AS Myt;

            void Register()
            {
                const auto &i = EFFECT_1;
                const auto &n = SPELL_AURA_DUMMY;
                const auto &m = AURA_EFFECT_HANDLE_REAL;
                OnEffectApply += AuraEffectApplyFn(Myt::applied, i, n, m);
                OnEffectRemove += AuraEffectRemoveFn(Myt::removed, i, n, m);
            }

            bool Validate(const SpellEntry *)
            {
                if (auto e = sSpellStore.LookupEntry(48366 /* Warning */))
                {
                    warning_entry() = std::move(e);
                    return true;
                }
                else
                    return false;
            }

            bool Load()
            {
                if (dynamic_cast<Player *>(GetUnitOwner()))
                {
                    warning_applied = false;
                    return true;
                }
                else
                    return false;
            }

            static const SpellEntry *&warning_entry()
            {
                static const SpellEntry *e;
                return e;
            }

            static bool in_area(Player &t)
            {
                if (t.GetZoneId() == 65 /* Dragonblight */)
                    switch (t.GetAreaId())
                    {
                    case 4177 /* Wintergarde Keep */:
                    case 4178 /* Wintergarde Mine */:
                    case 4188 /* The Carrion Fields */:
                        return true;
                    }
                return false;
            }

            void apply_warning(Player &t)
            {
                if (!warning_applied)
                {
                    t.CastSpell(&t, warning_entry(), true);
                    warning_applied = true;
                }
            }

            void unapply_warning(Player &t)
            {
                if (warning_applied)
                {
                    t.RemoveAura(warning_entry()->Id);
                    warning_applied = false;
                }
            }

            void applied
                (const AuraEffect *, const AuraApplication *, AuraEffectHandleModes mode)
            {
                auto &t = target();
                if (in_area(t))
                    ;
                else
                    apply_warning(t);
                connection = t.connect_area([this]()
                        {
                            auto &t = target();
                            if (in_area(t))
                                unapply_warning(t);
                            else
                                apply_warning(t);
                        }
                    );
            }

            void removed
                (const AuraEffect *, const AuraApplication *, AuraEffectHandleModes mode)
            {
                auto &t = target();
                t.disconnect_area(std::move(connection));
                unapply_warning(t);
            }

            Player &target()
            {
                return *static_cast<Player *>(GetUnitOwner());
            }

            const Player &target() const
            {
                return *static_cast<const Player *>(GetUnitOwner());
            }

            bool warning_applied;
            Player::Area_connection connection;
        };

        Wintergarde_gryphon_commander()
            : SpellScriptLoader("spell_gen_wintergarde_gryphon_commander")
        {
        }

        AuraScript *GetAuraScript() const
        {
            return new Wintergarde_gryphon_commander_AS;
        }
    };
}

void AddSC_generic_spell_scripts()
{
    new spell_gen_pet_summoned();
    new Purge_vehicle_control;
    new spell_gen_remove_flight_auras();
    new spell_creature_permanent_feign_death();
    new spell_pvp_trinket_wotf_shared_cd();
    new Wintergarde_gryphon_commander;
}