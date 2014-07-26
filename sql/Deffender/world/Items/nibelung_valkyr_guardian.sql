-- Val'kyr Guardian SAI
SET @ENTRY := 38391;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1500,2500,1500,2500,11,71841,0,0,0,0,0,2,0,0,0,0,0,0,0,"Val'kyr Guardian - Combat - Cast Smite every 1.5/2.5 seconds");

-- Val'kyr Protector SAI
SET @ENTRY := 38392;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1500,2500,1500,2500,11,71842,0,0,0,0,0,2,0,0,0,0,0,0,0,"Val'kyr Protector - Combat - Cast Smite every 1.5/2.5 seconds");

-- Damage values are (Val'kyr Guardian * 1.4). AP and dynamicflags are same as on Val'kyr Guardian
UPDATE `creature_template`
SET `mindmg` = 2227 , `maxdmg` = 2499, `attackpower` = 642, `minrangedmg` = 483, `maxrangedmg` = 712, `rangedattackpower` = 103, `dynamicflags` = 8
WHERE `entry` = 38392;