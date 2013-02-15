DELETE FROM `creature_loot_template` WHERE `entry`=33293;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(33293,40753,100,1,0,1,1),
(33293,1,100,1,0,-34121,2),
(33293,45867,0,2,2,1,1),
(33293,45868,0,2,2,1,1),
(33293,45869,0,2,2,1,1),
(33293,45870,0,2,2,1,1),
(33293,45871,0,2,2,1,1);

DELETE FROM `reference_loot_template` WHERE `entry`=34122;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(34122,45322,0,1,1,1,1),
(34122,45324,0,1,1,1,1),
(34122,45329,0,1,1,1,1),
(34122,45330,0,1,1,1,1),
(34122,45331,0,1,1,1,1),
(34122,45332,0,1,1,1,1),
(34122,45333,0,1,1,1,1),
(34122,45378,0,1,1,1,1),
(34122,45418,0,1,1,1,1),
(34122,45423,0,1,1,1,1);
