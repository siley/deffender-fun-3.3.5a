UPDATE `creature_template` SET `gossip_menu_id` = 0, `AIName` = '', `ScriptName` = 'npc_icc_buff' WHERE `entry` = 39371;

DELETE FROM `spell_area` WHERE `spell` IN ('73828', '73822');

INSERT INTO `spell_group`(`id`,`spell_id`) VALUES 
( '1472','73828'),
( '1472','73825'), 
( '1472','73824'), 
( '1472','73762');

INSERT INTO `spell_group_stack_rules`(`group_id`,`stack_rule`) VALUES ( '1472','1');  