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

namespace
{
    template<class Spell_script_type>
        SpellScript *get_spell_script()
    {
        return new Spell_script_type;
    }

    struct PvP_trinket
        : SpellScript
    {
        void Register()
        {
            EffectHandlers += EffectHandlerFn
                    (PvP_trinket::effect, EFFECT_FIRST_FOUND, SPELL_EFFECT_ANY);
        }

        bool Validate(const SpellEntry *spellEntry)
        {
            if (auto e = sSpellStore.LookupEntry
                        (72752 /* Will of the Forsaken Cooldown Trigger */))
            {
                entry = std::move(e);
                return true;
            }
            else
                return false;
        }

        bool Load()
        {
            if (auto p = dynamic_cast<Player *>(GetCaster()))
            {
                caster = std::move(p);
                return true;
            }
            else
                return false;
        }

        void effect(SpellEffIndex)
        {
            caster->AddSpellAndCategoryCooldowns(entry, 0);
            WorldPacket msg(SMSG_SPELL_COOLDOWN, 8 + 1 + 4 + 4);
            msg << caster->GetGUID() << uint8(0) << entry->Id << uint32(0);
            caster->SendDirectMessage(&msg);
        }

        static const SpellEntry *entry;
        Player *caster;
    };

    const SpellEntry *PvP_trinket::entry;

    struct Will_of_the_forsaken
        : SpellScript
    {
        void Register()
        {
            EffectHandlers += EffectHandlerFn
                    (Will_of_the_forsaken::effect, EFFECT_FIRST_FOUND, SPELL_EFFECT_ANY);
        }

        bool Validate(const SpellEntry *spellEntry)
        {
            if (auto e = sSpellStore.LookupEntry
                        (72757 /* Will of the Forsaken Cooldown Trigger (WOTF) */))
            {
                entry = std::move(e);
                return true;
            }
            else
                return false;
        }

        bool Load()
        {
            if (auto p = dynamic_cast<Player *>(GetCaster()))
            {
                caster = std::move(p);
                return true;
            }
            else
                return false;
        }

        void effect(SpellEffIndex)
        {
            caster->AddSpellAndCategoryCooldowns(entry, 0);
            WorldPacket msg(SMSG_SPELL_COOLDOWN, 8 + 1 + 4 + 4);
            msg << caster->GetGUID() << uint8(0) << entry->Id << uint32(0);
            caster->SendDirectMessage(&msg);
        }

        static const SpellEntry *entry;
        Player *caster;
    };

    const SpellEntry *Will_of_the_forsaken::entry;
}

void AddSC_generic_spell_scripts()
{
    Script *newscript = new Script;
    newscript->Name = "spell_gen_pvp_trinket";
    newscript->GetSpellScript = &get_spell_script<PvP_trinket>;
    newscript->RegisterSelf();
    newscript = new Script;
    newscript->Name = "spell_gen_will_of_the_forsaken";
    newscript->GetSpellScript = &get_spell_script<Will_of_the_forsaken>;
    newscript->RegisterSelf();
}