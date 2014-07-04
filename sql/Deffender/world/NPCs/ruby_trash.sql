INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES (40081, 40468, 2, 1, 'Orb Carrier', 6, 30000);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES (40081, 40469, 3, 1, 'Orb Carrier', 6, 30000);


-- Charscale Invoker SAI
SET @ENTRY := 40417;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,8000,9000,30000,31000,11,75413,0,0,0,0,0,1,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)"),
(@ENTRY,0,1,0,0,0,100,0,5000,6000,5000,6000,11,75412,0,0,0,0,0,2,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");

-- Charscale Assaulter SAI
SET @ENTRY := 40419;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,5000,6000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)"),
(@ENTRY,0,1,0,0,0,100,0,8000,9000,15000,16000,11,75417,0,0,0,0,0,5,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");

-- Charscale Elite SAI
SET @ENTRY := 40421;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,8000,9000,11,15621,0,0,0,0,0,2,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");

-- Charscale Commander SAI
SET @ENTRY := 40423;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,6000,5000,6000,11,13737,0,0,0,0,0,2,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)"),
(@ENTRY,0,1,0,0,0,100,0,1000,1100,5000,6000,75,75416,0,0,0,0,0,11,0,8,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");