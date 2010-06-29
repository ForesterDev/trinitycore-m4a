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

#ifndef DEF_ULDUAR_H
#define DEF_ULDUAR_H

enum
{
    boss_leviathan,
    boss_ignis,
    boss_razorscale,
    boss_xt002,
    boss_assembly,
    boss_kologarn,
    boss_auriaya,
    boss_mimiron,
    boss_hodir,
    boss_thorim,
    boss_freya,
    boss_vezax,
    boss_yoggsaron,
    boss_algalon,
    num_bosses
};

enum eTypes
{
    DATA_COLOSSUS               = 14,
    DATA_STEELBREAKER           = 20,
    DATA_MOLGEIM                = 21,
    DATA_BRUNDIR                = 22,
    DATA_RUNEMASTER_MOLGEIM     = 23,
    DATA_STORMCALLER_BRUNDIR    = 24,    

    NPC_LEVIATHAN               = 33113,
    NPC_IGNIS                   = 33118,
    NPC_RAZORSCALE              = 33186,
    NPC_XT002                   = 33293,
    NPC_STEELBREAKER            = 32867,
    NPC_MOLGEIM                 = 32927,
    NPC_BRUNDIR                 = 32857,
    NPC_KOLOGARN                = 32930,
    NPC_AURIAYA                 = 33515,
    NPC_MIMIRON                 = 33350,
    NPC_HODIR                   = 32845,
    NPC_THORIM                  = 32865,
    NPC_FREYA                   = 32906,
    NPC_VEZAX                   = 33271,
    NPC_YOGGSARON               = 33288,
    NPC_ALGALON                 = 32871,

    EVENT_TOWER_OF_STORM_DESTROYED     = 21031,
    EVENT_TOWER_OF_FROST_DESTROYED     = 21032,
    EVENT_TOWER_OF_FLAMES_DESTROYED    = 21033,
    EVENT_TOWER_OF_LIFE_DESTROYED      = 21030
};

enum
{
    data64_leviathan = 0,
    data64_ignis = 1,
    data64_razorscale = 2,
    data64_xt002 = 3,
    data64_kologarn = 5,
    data64_auriaya = 6,
    data64_mimiron = 7,
    data64_hodir = 8,
    data64_thorim = 9,
    data64_freya = 10,
    data64_vezax = 11,
    data64_yoggsaron = 12,
    data64_algalon = 13,
};

#endif
