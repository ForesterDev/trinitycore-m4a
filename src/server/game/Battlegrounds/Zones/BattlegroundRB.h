/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
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

#ifndef __BATTLEGROUNDRB_H
#define __BATTLEGROUNDRB_H

#include <memory>
#include <array>
#include "Battleground.h"

class Battleground;

class BattlegroundRBScore : public BattlegroundScore
{
    public:
        BattlegroundRBScore() {};
        virtual ~BattlegroundRBScore() {};

        std::pair<std::size_t, Stat_data_type> stat_data() const
        {
            std::array<int32, max_stats> d;
            auto first = d.begin(), it = first;
            return std::make_pair(it - first, std::move(d));
        }
};

class BattlegroundRB : public Battleground
{
    friend class BattlegroundMgr;

    public:
        BattlegroundRB();
        ~BattlegroundRB();
        void Update(uint32 diff);

        virtual void AddPlayer(Player *plr);
        virtual void StartingEventCloseDoors();
        virtual void StartingEventOpenDoors();

        void RemovePlayer(Player *plr,uint64 guid);
        void HandleAreaTrigger(Player *Source, uint32 Trigger);

        /* Scorekeeping */
        void UpdatePlayerScore(Player *Source, uint32 type, uint32 value, bool doAddHonor = true);

    private:
};
#endif
