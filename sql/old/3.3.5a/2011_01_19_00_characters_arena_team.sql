ALTER TABLE `arena_team` 
CHANGE `name` `name` VARCHAR(24) NOT NULL,
CHANGE `EmblemStyle` `EmblemStyle` TINYINT(3) UNSIGNED DEFAULT '0' NOT NULL,
CHANGE `BorderStyle` `BorderStyle` TINYINT(3) UNSIGNED DEFAULT '0' NOT NULL;