INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES ('37552', '530', '1', '1', '0', '0', '11800.1', '-7064.56', '25.2364', '2.769', '300', '0', '0', '123', '180', '0', '0', '0', '0');
UPDATE `creature_template` SET `dynamicflags`='32', `npcflag`='1', `AIName`='SmartAI' WHERE (`entry`='37552');
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES ('37601', '530', '1', '0', '0', '0', '11802.9', '-7064.22', '25.724', '3.30072', '300', '0', '0', '42', '0', '0', '0', '33554432', '0');
INSERT INTO `smart_scripts` (`entryorguid`, `event_type`, `action_type`, `action_param1`, `target_type`, `comment`) VALUES ('37552', '64', '33', '37601', '7', 'On gossip hello - give quest credit - Thalorien Dawnseeker\'s Remains');
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES(15, 37523, 0, 0, 0, 9, 0, 24595, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES(15, 37523, 1, 0, 0, 9, 0, 24553, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES(15, 37523, 2, 0, 0, 9, 0, 24598, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES(15, 37523, 3, 0, 0, 9, 0, 24596, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES(15, 37523, 4, 0, 0, 9, 0, 24594, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES(15, 37523, 5, 0, 0, 9, 0, 24564, 0, 0, 0, 0, '', NULL);
INSERT INTO `gossip_menu_option` VALUES(37552, 37552, 0, 'Examine the remains.', 1, 1, 0, 0, 0, 0, NULL);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(37552, 15155);

INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES(37158, 50254, -100, 1, 0, 1, 1);

INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES(37158, 668, 3, 99, 0, 5304.5, 2001.35, 709.341, 4.15073, 7200, 0, 0, 214200, 0, 0, 0, 0, 0);

INSERT INTO `gameobject` VALUES
(500001, 201794, 580, 1, 1, 1694.95, 604.023, 28.1494, 5.95759, 0, 0, 0.162079, -0.986778, -30, 100, 1);

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES(300246, 580, 1, 1, 1694.95, 604.023, 28.1494, 5.95759, 0, 0, 0.162079, -0.986778, -120, 100, 1);
36954


UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='37523');

INSERT INTO `spell_target_position` VALUES(70746, 0, 580, 1676.05, 577.531, 31.3236, 1.09912);

INSERT INTO `smart_scripts` VALUES(37523, 0, 0, 0, 62, 0, 100, 0, 37523, 0, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Script  for http://ru.wowhead.com/npc=37523');
INSERT INTO `smart_scripts` VALUES(37523, 0, 1, 0, 62, 0, 100, 0, 37523, 1, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Script  for http://ru.wowhead.com/npc=37523');
INSERT INTO `smart_scripts` VALUES(37523, 0, 2, 0, 62, 0, 100, 0, 37523, 2, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Script  for http://ru.wowhead.com/npc=37523');
INSERT INTO `smart_scripts` VALUES(37523, 0, 3, 0, 62, 0, 100, 0, 37523, 3, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Script  for http://ru.wowhead.com/npc=37523');
INSERT INTO `smart_scripts` VALUES(37523, 0, 4, 0, 62, 0, 100, 0, 37523, 4, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Script  for http://ru.wowhead.com/npc=37523');
INSERT INTO `smart_scripts` VALUES(37523, 0, 5, 0, 62, 0, 100, 0, 37523, 5, 0, 0, 11, 70746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Script  for http://ru.wowhead.com/npc=37523');

INSERT INTO `gossip_menu_option` VALUES(37523, 0, 0, 'I''m ready to enter the Sunwell.', 1, 1, 0, 0, 0, 0, NULL);
INSERT INTO `gossip_menu_option` VALUES(37523, 1, 0, 'I''m ready to enter the Sunwell.', 1, 1, 0, 0, 0, 0, NULL);
INSERT INTO `gossip_menu_option` VALUES(37523, 2, 0, 'I''m ready to enter the Sunwell.', 1, 1, 0, 0, 0, 0, NULL);
INSERT INTO `gossip_menu_option` VALUES(37523, 3, 0, 'I''m ready to enter the Sunwell.', 1, 1, 0, 0, 0, 0, NULL);
INSERT INTO `gossip_menu_option` VALUES(37523, 4, 0, 'I''m ready to enter the Sunwell.', 1, 1, 0, 0, 0, 0, NULL);
INSERT INTO `gossip_menu_option` VALUES(37523, 5, 0, 'I''m ready to enter the Sunwell.', 1, 1, 0, 0, 0, 0, NULL);

INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES(201794, 49871, -100, 1, 0, 1, 1);

INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES(22833, 0, 9, 72796, 600, 0, 0, 0, 0, 0);
