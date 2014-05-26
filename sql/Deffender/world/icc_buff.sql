DELETE FROM `gossip_menu` WHERE `entry` = '400';
INSERT INTO `gossip_menu`(`entry`,`text_id`) VALUES ( '400','15602'); 

DELETE FROM `smart_scripts` WHERE (`entryorguid`=39371 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39371, 0, 0, 0, 62, 0, 100, 0, 400, 400, 0, 0, 28, 73828, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Unaura icc buff");

UPDATE `creature_template` SET `gossip_menu_id` = "400", `AIName` = "SmartAI" WHERE `entry` = '39371';

DELETE FROM `gossip_menu_option`  WHERE `menu_id` = '400' AND `id` = '400';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES('400','400','0','I don\'t need help.','0','1','1','0','0','0','0',NULL,'0');

DELETE FROM `spell_area` WHERE `spell`='73828';