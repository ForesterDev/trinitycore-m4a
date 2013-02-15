DELETE FROM `areatrigger_scripts` WHERE `entry` = 5697;
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES
(5697,"hor_altar_trigger");

UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 1 WHERE `entry` IN (38599, 38603);


UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_frostworn_general' WHERE `entry`=36723;
 
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_and_sylvana_hor_part2' WHERE `entry` IN (36955, 37554);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='boss_lich_king_hor' WHERE `entry`=37226;
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_raging_gnoul' WHERE `entry`=36940;
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_risen_witch_doctor' WHERE `entry`=36941;
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_lumbering_abomination' WHERE `entry`=37069;

UPDATE `creature_template` SET faction_A = 16, faction_H = 16, equipment_id = 2437 WHERE `entry`=37720;

DELETE FROM `creature` WHERE `guid` IN (202294,202301) AND `id` IN (37225,37226); -- Remove DB spawned Uther and Event LK