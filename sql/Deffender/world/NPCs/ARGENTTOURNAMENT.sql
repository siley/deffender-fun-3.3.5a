-- Cast Armistice in front of the pavillions as well
DELETE FROM `spell_area` WHERE `spell`=64373 AND `area` IN (4676, 4677);
INSERT INTO `spell_area` (`spell`,`area`,`quest_start`,`quest_end`,`aura_spell`,`racemask`,`gender`,`autocast`) VALUES
(64373,4676,0,0,0,0,2,1), -- Sunreaver Pavillion
(64373,4677,0,0,0,0,2,1); -- SIlver Covenant Pavillion

-- TEMP disable defunct quests
DELETE FROM`disables`WHERE`sourceType`=1 AND`entry`IN(14090,14141);
INSERT INTO`disables`(`sourceType`,`entry`,`comment`) VALUES 
(1,14090,'Gormok Wants His Snobolds - Aliance'),
(1,14141,'Gormok Wants His Snobolds - Horde');

-- TEMP adjust speed of some NPCs and mounts (mounts at colliseum has speed 1.57143)
UPDATE creature_template SET speed_run=1.35 WHERE entry IN (33285,33306,33384,33383,33382,33561,33564,33558,33559,33562,33448); -- Valiants - 1.14286
UPDATE creature_template SET speed_run=1.5 WHERE entry IN (33739,33749,33745,33744,33748,33740,33743,33747,33738,33746,33707); -- Champions - 1.14286
UPDATE creature_template SET speed_run=1.9 WHERE entry IN (34127); -- Boneguard Commander - 1.14286 ... lieutenant has 2
UPDATE creature_template SET speed_run=1.55 WHERE entry IN (33785); -- Black Knight - 1.14286

-- make mounts immune to daze
UPDATE creature_template SET mechanic_immune_mask=mechanic_immune_mask|0x04000000 WHERE entry IN (33531,33782); -- Campaign Warhorse, Argent Warhorse (0)

-- fix stormwind champion (q Among the Champions)
UPDATE`creature_template`SET`flags_extra`=0 WHERE`entry`=33747;

-- --------------------------------------------------------------------------------------------------------------------------------------

-- A Blade Fit For A Champion
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (19,20) AND `SourceEntry` IN (13794,13795);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES
-- Eadric the pure 13794 - Needs rewarded A Champion Rises
(19,13794,0,8,13702,0,0,0, NULL), -- Human
(19,13794,1,8,13732,0,0,0, NULL), -- Dwarf
(19,13794,2,8,13735,0,0,0, NULL), -- NElf
(19,13794,3,8,13733,0,0,0, NULL), -- Gnome
(19,13794,4,8,13734,0,0,0, NULL), -- Draenei
(19,13794,5,8,13736,0,0,0, NULL), -- Orc
(19,13794,6,8,13737,0,0,0, NULL), -- Troll
(19,13794,7,8,13738,0,0,0, NULL), -- Tauren
(19,13794,8,8,13739,0,0,0, NULL), -- Undead
(19,13794,9,8,13740,0,0,0, NULL), -- BElf
-- The Scourgebane 13795 - Needs rewarded A Champion Rises
(19,13795,0,8,13702,0,0,0, NULL), -- Human
(19,13795,1,8,13732,0,0,0, NULL), -- Dwarf
(19,13795,2,8,13735,0,0,0, NULL), -- NElf
(19,13795,3,8,13733,0,0,0, NULL), -- Gnome
(19,13795,4,8,13734,0,0,0, NULL), -- Draenei
(19,13795,5,8,13736,0,0,0, NULL), -- Orc
(19,13795,6,8,13737,0,0,0, NULL), -- Troll
(19,13795,7,8,13738,0,0,0, NULL), -- Tauren
(19,13795,8,8,13739,0,0,0, NULL), -- Undead
(19,13795,9,8,13740,0,0,0, NULL), -- BElf
-- dtto 20
-- Eadric the pure 13794 - Needs rewarded A Champion Rises
(20,13794,0,8,13702,0,0,0, NULL), -- Human
(20,13794,1,8,13732,0,0,0, NULL), -- Dwarf
(20,13794,2,8,13735,0,0,0, NULL), -- NElf
(20,13794,3,8,13733,0,0,0, NULL), -- Gnome
(20,13794,4,8,13734,0,0,0, NULL), -- Draenei
(20,13794,5,8,13736,0,0,0, NULL), -- Orc
(20,13794,6,8,13737,0,0,0, NULL), -- Troll
(20,13794,7,8,13738,0,0,0, NULL), -- Tauren
(20,13794,8,8,13739,0,0,0, NULL), -- Undead
(20,13794,9,8,13740,0,0,0, NULL), -- BElf
-- The Scourgebane 13795 - Needs rewarded A Champion Rises
(20,13795,0,8,13702,0,0,0, NULL), -- Human
(20,13795,1,8,13732,0,0,0, NULL), -- Dwarf
(20,13795,2,8,13735,0,0,0, NULL), -- NElf
(20,13795,3,8,13733,0,0,0, NULL), -- Gnome
(20,13795,4,8,13734,0,0,0, NULL), -- Draenei
(20,13795,5,8,13736,0,0,0, NULL), -- Orc
(20,13795,6,8,13737,0,0,0, NULL), -- Troll
(20,13795,7,8,13738,0,0,0, NULL), -- Tauren
(20,13795,8,8,13739,0,0,0, NULL), -- Undead
(20,13795,9,8,13740,0,0,0, NULL); -- BElf
-- SELECT * FROM `character_queststatus_rewarded` WHERE quest IN (13794,13795)
-- DELETE FROM `character_queststatus_rewarded` WHERE quest IN (13794,13795); -- to remove quests from players who completed them before this fix

-- DK Quest Restriction -- The Scourgebane
UPDATE `quest_template` SET `RequiredClasses`= 32 WHERE `ID`=13795;
-- Non DK Quest Restriction -- Eadric The Pure
UPDATE `quest_template` SET `RequiredClasses`= 1503 WHERE `ID`=13794;

-- DELETE FROM character_queststatus WHERE quest IN (13794,13795);
-- DELETE FROM character_queststatus_rewarded WHERE quest IN (13794,13795);

-- Crusader dailies (require title <Crusader> = exalted with Crusade and Alliance/Horde+have the right to represent them), one of each group per dey = achievement 2816 or 2817
	-- Mistcaller Yngvar
	-- Drottinn Hrothgar
	-- Ornolf The Scarred
	-- Deathspeaker Kharos
UPDATE `quest_template` SET `ExclusiveGroup`=14101 WHERE `ID` IN (14102, 14101, 14104, 14105);
	-- The Fate Of The Fallen
	-- Get Kraken!
	-- Identifying the Remains
UPDATE `quest_template` SET `ExclusiveGroup`=14107 WHERE `ID` IN (14107, 14108, 14095);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (19,20) AND `SourceEntry` IN (14102, 14101, 14104, 14105,  14107, 14108, 14095);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`Comment`) VALUES
(19,14102,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- Mistcaller Yngvar
(19,14102,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14102,0,17,2816, 'Requires Exalted Argent Champion of the Horde'),
(20,14102,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(19,14101,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- Drottinn Hrothgar
(19,14101,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14101,0,17,2816, 'Requires Exalted Argent Champion of the Horde'),
(20,14101,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(19,14104,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- Ornolf The Scarred
(19,14104,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14104,0,17,2816, 'Requires Exalted Argent Champion oGf the Horde'),
(20,14104,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(19,14105,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- Deathspeaker Kharos
(19,14105,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14105,0,17,2816, 'Requires Exalted Argent Champion of the Horde'),
(20,14105,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(19,14107,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- The Fate Of The Fallen
(19,14107,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14107,0,17,2816, 'Requires Exalted Argent Champion of the Horde'),
(20,14107,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(19,14108,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- Get Kraken!
(19,14108,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14108,0,17,2816, 'Requires Exalted Argent Champion of the Horde'),
(20,14108,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(19,14095,0,17,2816, 'Requires Exalted Argent Champion of the Horde'), -- Identifying the Remains
(19,14095,1,17,2817, 'Requires Exalted Argent Champion of the Alliance'),
(20,14095,0,17,2816, 'Requires Exalted Argent Champion of the Horde'),
(20,14095,1,17,2817, 'Requires Exalted Argent Champion of the Alliance');



-- Covenant Quests (requires exalted with Silver Covenant/Sunreavers + being a champion of at least one race)
UPDATE `quest_template` SET `PrevQuestId`=13700, `RequiredMinRepFaction`=1094, `RequiredMinRepValue`=42000 WHERE `ID` IN (14112, 14076, 14090, 14096, 14152, 14080, 14077, 14074); -- Alliance
UPDATE `quest_template` SET `PrevQuestId`=13701, `RequiredMinRepFaction`=1124, `RequiredMinRepValue`=42000 WHERE `ID` IN (14145, 14092, 14141, 14142, 14136, 14140, 14144, 14143); -- Horde
	-- What Do You Feed A Yeti, Anyway?
	-- Breakfast Of Champions
	-- Gormok Wants His Snobolds
UPDATE `quest_template` SET `ExclusiveGroup`=14112 WHERE `ID` IN (14112, 14145, 14076, 14092, 14090, 14141); -- A1, H1, A2, H2, A3, H3
	-- Rescue At Sea
	-- Stop The Agressors
	-- The Light's Mercy
	-- A Leg Up
UPDATE `quest_template` SET `ExclusiveGroup`=14152 WHERE `ID` IN (14152, 14136, 14080, 14140, 14077, 14144, 14074, 14143); -- A1, H1, A2, H2, A3, H3, A4, H4
-- You've Really Done It This Time, Kul - aviable every day

-- Champion Marker - required for Contributin' To The Cause
-- UPDATE `quest_template` SET `NextQuestId`=13846 WHERE `entry` IN (13700, 13701); -- Alliance, Horde

-- Champion Dailies
	-- Among The Champions 13790,13793,13811,13814
	-- Battle Before The Citadel 13861,13864,13862,13863
	-- Taking Battle To The Enemy 13789,13791,13810,13813
	-- Threat From Above 13682,13788,13809,13812 -- requires The Black Knight's Fall as well -- so commented out as rev fac56ea88ea483bdee5bd4bbb9ef368a82a45a5e sets PrevQuestId to 13664
UPDATE `quest_template` SET `PrevQuestId`=13794 WHERE `ID` IN (13861,13862,/*13682,*/13789,13790,/*13809,*/13810,13811); -- non-DK
UPDATE `quest_template` SET `PrevQuestId`=13795 WHERE `ID` IN (13863,13864,/*13788,*/13791,13793,/*13812,*/13813,13814); -- DK

-- BK chain:
UPDATE `quest_template` SET `PrevQuestId`=13700 WHERE `ID`=13633; -- The Black Knight of Westfall? (Ally)
UPDATE `quest_template` SET `PrevQuestId`=13701 WHERE `ID`=13634; -- The Black Knight of Silverpine (Horde)

-- Melee target spell counterattack - na mounty
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=62709;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`Comment`) VALUES
(13,62709,1,18,1,33844, 'Counterattack on Sunreaver Hawskstrider'),
(13,62709,2,18,1,33845, 'Counterattack on Quel''dorei Steed');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (62552,62719);
INSERT INTO `spell_script_names` (spell_id,ScriptName) VALUES
(62552,'spell_defend'),
(62719,'spell_defend');

/*-- summony - target -- maybe cannot be used for this spells ... nope
DELETE FROM `spell_target_position` WHERE `id` IN (63026,63173);
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(63026,571,8575.451, 952.472,547.554,0.38),
(63173,571,8562.837,1099.154,556.788,5.03);*/

-- Goblin Dailies (removed in 3.2)
DELETE FROM `creature_queststarter` WHERE `quest` IN (13820, 13681, 13627);
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES
(33817, 13820), -- The Blastbolt Brothers
-- (33435, 13681), -- A Chip Off the Ulduar Block
(33434, 13627); -- Jack Me Some Lumber

DELETE FROM `creature_questender` WHERE `quest` IN (13820, 13681, 13627);
INSERT INTO `creature_questender` (`id`, `quest`) VALUES
(33434, 13820), -- The Blastbolt Brothers
(33435, 13681), -- A Chip Off the Ulduar Block
(33434, 13627); -- Jack Me Some Lumber

UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry` IN (33435,33434);
-- Jack me some lumber
-- -- At The Enemy's Gates/Battle Before The Citadel -- --
UPDATE `creature` SET `orientation`='0.715585' WHERE `guid` =207528; -- 2.0944e+06 -- That boneguard footman was spinning very fast

-- trample scourge - na "boneguard foorman"
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=63001;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`Comment`) VALUES
(13,63001,0,18,1,33438, 'Trample Scourge on Boneguard Footman');
-- need to fix spell 63000 (periodic dummy) ... done

-- Boneguard footman: increase damage
UPDATE `creature_template` SET `dmg_multiplier`='4' WHERE`entry` =33438; -- 1

-- Boneguard Lietenant: add some auras 62710 (Strong Guy Sundering Thrust Aura) + 64100 (Defend - maybe not the correct one) ... in addition he should use 63010 (and maybe valiant-like script)
-- UPDATE `creature_template_addon` SET `auras`='62710 64100' WHERE `entry`=33429;
UPDATE `creature_template_addon` SET `auras`='64100' WHERE `entry`=33429;

-- Boneguard Commander
UPDATE `creature_template` SET `scriptname`='npc_boneguard_commander' WHERE `entry`=34127;

-- some EventAI
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry` IN (33550,33429/*,34127*/);

-- link 62563 -> 68321 (?)
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=62563;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(62563,68321,0,'cast charge when cast charge :D');

-- Fix Quest There's Something About the Squire (http://www.wowhead.com/quest=13654)
-- From aspirine-core
UPDATE `creature_template` SET `scriptname`='npc_maloric' WHERE `entry`=33498;
-- Conditions
DELETE FROM `conditions` WHERE `SourceEntry`=45080 AND `ConditionValue1`=33498;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ErrorTextId`,`Comment`) VALUES
(18,45080,1,24,1,33498,447,'Item Large Femur - Npc Maloric');
-- loot item Large Femur
UPDATE `creature_template` SET lootid=33499 WHERE `entry`=33499;
DELETE FROM `creature_loot_template` WHERE `item`=45080;
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
(33499,45080,-100,1,0,1,1);

-- Add Scripts to NPCs
UPDATE `creature_template` SET `ScriptName`='npc_valis_windchaser' WHERE `entry`=33974;
UPDATE `creature_template` SET `ScriptName`='npc_rugan_steelbelly' WHERE `entry`=33972;
UPDATE `creature_template` SET `ScriptName`='npc_jeran_lockwood' WHERE `entry`=33973;
UPDATE `creature_template` SET `ScriptName`='npc_squire_danny' WHERE `entry`=33518;
UPDATE `creature_template` SET `ScriptName`='npc_training_dummy_argent' WHERE `entry` IN (33229,33272,33243);
UPDATE `creature_template` SET `ScriptName`='npc_vendor_argent_tournament' WHERE `entry` IN (33657, 33653, 33307, 33310, 33650, 33557, 33555, 33553, 33556, 33554);

-- Quest Support Among the Champions 13790-13811-13793-13814
UPDATE `creature_template` SET `ScriptName`='npc_faction_champion' WHERE `entry` IN (33739,33749,33745,33744,33748,33740,33743,33747,33738,33746);
-- Quest The Grand Melee Quests 13665-13745-13750-13756-13761-13767-13772-13777-13782-13787.- http://www.wowhead.com/search?q=The+Grand+Melee
UPDATE `creature_template` SET `ScriptName`='npc_faction_valiant' WHERE `entry` IN (33285,33306,33384,33383,33382,33561,33564,33558,33559,33562);

-- Quest 13666 & 13673:  A Blade Fit For A Champion!
-- Maiden Of Ahswood Lake
UPDATE `creature_template` SET `npcflag`=`npcflag`|1, `ScriptName`='npc_maiden_of_ashwood_lake' WHERE `entry`=33220;
-- Lake Frog
UPDATE `creature_template` SET `ScriptName`='npc_lake_frog' WHERE `entry`=33211;
UPDATE creature_template SET speed_run=1, speed_walk=1.6 WHERE entry=33211; -- frog speed from sniff
-- update respawn and movement
UPDATE creature SET spawntimesecs=20,spawndist=15,MovementType=1 WHERE id=33211;
-- Quest: Edge of Winter zmena dmg u Lord Everblaze
UPDATE `creature_template` SET `dmg_multiplier`='6' WHERE `entry`=33289 AND dmg_multiplier <1.1; -- 1

-- Quest: A Worthy weapon
DELETE FROM `event_scripts` WHERE `id`=20990;
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `x`, `y`, `z`, `o`) VALUES (20990, 0, 10, 33273, 42000, 4602.977, -1600.141, 156.7834, 0.7504916);
UPDATE `creature_template` SET `InhabitType`=5, `ScriptName`='npc_maiden_of_drak_mar' WHERE `entry`=33273;
DELETE FROM `creature_template_addon` WHERE `entry`=33273;
INSERT INTO `creature_template_addon` (`entry`, `emote`) VALUES (33273, 13); -- 13 = EMOTE_STATE_SIT (not working :-/ )
-- + need to spawn GO 300009
DELETE FROM gameobject WHERE guid=1000002 AND id=300009;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(1000002,300009,571,1,1,4603.75,-1600.14,156.657,1.70693,0,0,0.753563,0.657375,300,0,1);

-- champion
UPDATE `creature_template` SET `movementId`=48,`ScriptName`='npc_argent_champion' WHERE `entry`=33707;
DELETE FROM `creature_template_addon` WHERE `entry`=33707;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(33707,0,28918,0,0,0,NULL);-- Mount

-- Texts
DELETE FROM `creature_text` WHERE `entry`<=-1850000 AND `entry`>=-1850015 ;
INSERT INTO `creature_text` (`entry`, `id`, `text`, `comment`) VALUES
-- Maiden of Drak'mar http://www.youtube.com/watch?v=TCC3qayUn3o
(0, 1850000, 'Are those winter hyacinths? For me?', 'NPC_TEXTID_MAIDEN_OF_DRAK_MAR_01'),
(0, 1850001, 'It''s been so long since a traveler has come here bearing flowers.', 'NPC_TEXTID_MAIDEN_OF_DRAK_MAR_02'),
(0, 1850002, 'The lake has been lonely these past years. The travelers stopped coming and evil came to these waters.', 'NPC_TEXTID_MAIDEN_OF_DRAK_MAR_03'),
(0, 1850003, 'Your gift is a rare kindness, traveler. Please take this blade with my gratitude. Long ago, another traveler left it here, but i have little use for it.','NPC_TEXTID_MAIDEN_OF_DRAK_MAR_04'),
-- Faction Valiant http://www.youtube.com/watch?v=veG-xl0kRdE
(0, 1850004, 'Let it begin!','NPC_FACTION_VAILIANT_TEXT_SAY_START_1'), -- ? Stand ready !
(0, 1850005, 'Let the battle begin!', 'NPC_FACTION_VAILIANT_TEXT_SAY_START_2'),
(0, 1850006, 'Prepare your self !', 'NPC_FACTION_VAILIANT_TEXT_SAY_START_3'),
-- Faction Valiant (again)
(0, 1850010, 'I stand defeated. Nice battle !', 'NPC_FACTION_VAILIANT_TEXT_SAY_WIN_1'),
(0, 1850011, 'It seems that I''ve underestimated your skills. Well done.', 'NPC_FACTION_VAILIANT_TEXT_SAY_WIN_2'),
(0, 1850012, 'I''ve won. You''ll probably have more luck next time.', 'NPC_FACTION_VAILIANT_TEXT_SAY_LOOSE'),
-- Argent Valiant
(0, 1850007, 'You think you have the courage?  We shall see.', 'NPC_ARGENT_VAILIANT_TEXT_SAY_START'),
(0, 1850008, 'Impressive demonstration. I think you''re able to join the ranks of the valiants.', 'NPC_ARGENT_VAILIANT_TEXT_SAY_WIN'),
(0, 1850009, 'I''ve won. You''ll probably have more luck next time.', 'NPC_ARGENT_VAILIANT_TEXT_SAY_LOOSE'),
-- npc_maiden_of_ashwood_lake
(0, 1850015,'Can it really be? Free after all these years?','NPC_MAIDEN_ASHWOOD_TEXT_SAY_FREED'),
-- argent champion - asi pouziva kecy od valianta
(0, 1850013,'You believe you are ready to be a champion? Defend yourself!','NPC_ARGENT_CHAMPION_TEXT_SAY_START'),
(0, 1850014,'Most impressive. You are worthy to gain the rank of champion!','NPC_ARGENT_CHAMPION_TEXT_SAY_WIN');

/*
You think you are ready to become a champion. We shall see.
You have been defeated. But do not give up. I sense that one day you will join our ranks as a champion.
Most impressive. You are worthy to gain the rank of champion.
You have shown that you are ready for the rank of champion.

Argent Valiant says: The rank of valiant is not easily won. Prepare yourself!
Argent Valiant says: You believe yourself ready for the rank of valiant? We shall see.

Argent Valiant says: I'm afraid you are not ready to become a valiant. However I suspect you will be ready soon enough.
Argent Valiant says: It would seem that you are not yet ready for the rank of valiant. Some more training may serve you well.

Argent Valiant says: Impressive skills indeed. I believe that you are more than ready for the rank of valiant.
Argent Valiant says: Well done! It seems that you are worthy of the valiant rank!
*/
-- Mastery of ...
DELETE FROM `creature_text` WHERE `entry` IN (33972,33973,33974);
INSERT INTO `creature_text` (entry,groupid,id,TEXT,TYPE,LANGUAGE,sound,COMMENT) VALUE
(33972,0,0,'Use Shield-Breaker on a Charge Target. \nFollow up with Charge while the target is vulnerable.',5,0,0,'Rugan Steelbelly''s advice'),
(33973,0,0,'Put up Defend and then use Thrust on a Melee Target.',5,0,0,'Jeran Lockwood''s advice'),
(33974,0,0,'Use Shield-Breaker on a Ranged Target. \nThen use Shield-Breaker while it is defenseless.',5,0,0,'Valis Windchaser''s advice');
-- there should be image as well ... like |TInterface\\Icons\\INV_Misc_Coin_01:16|t
-- Shield-Breaker:
-- Charge:
-- Thrust:

-- Ajouts des spellclick_spells pour les montures à l'écurie - v TDB je toho min - v TDB je asi jen aspirant a "A Valiant" + vsude je aurarequired=62853
DELETE FROM `npc_spellclick_spells` WHERE npc_entry IN (33842,33796,33798,33791,33792,33799);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(33842, 63791, 1, 0), -- Aspirant
(33799, 62783, 1, 0), -- A Valiant Of Orgrimmar
(33799, 62783, 1, 0), -- Valiant Of Orgrimmar
(33796, 62784, 1, 0), -- A Valiant Of Sen'jin
(33796, 62784, 1, 0), -- Valiant Of Sen'jin
(33792, 62785, 1, 0), -- A Valiant Of Thunder Bluff
(33792, 62785, 1, 0), -- Valiant Of Thunder Bluff
(33791, 62786, 1, 0), -- A Valiant Of Silvermoon
(33791, 62786, 1, 0), -- Valiant Of Silvermoon
(33798, 62787, 1, 0), -- A Valiant Of Undercity
(33798, 62787, 1, 0); -- Valiant Of Undercity
DELETE FROM `npc_spellclick_spells` WHERE npc_entry IN (33843,33800,33795,33790,33793,33794);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(33843, 63792, 1, 0), -- Aspirant
(33800, 62774, 1, 0), -- A Valiant Of Stormwind
(33800, 62774, 1, 0), -- Valiant Of Stormwind
(33795, 62779, 1, 0), -- A Valiant Of Ironforge
(33795, 62779, 1, 0), -- Valiant Of Ironforge
(33793, 62780, 1, 0), -- A Valiant Of Gnomregan
(33793, 62780, 1, 0), -- Valiant Of Gnomregan
(33790, 62781, 1, 0), -- A Valiant Of Exodar
(33790, 62781, 1, 0), -- Valiant Of Exodar
(33794, 62782, 1, 0), -- A Valiant Of Darnassus
(33794, 62782, 1, 0); -- Valiant Of Darnassus

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `ConditionValue1`=62853;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`Comment`) VALUES
(17,63791,1,62853, 'Aspirant'),
(17,63792,1,62853, 'Aspirant'),
(17,62783,1,62853, 'Orgrimmar'),
(17,62784,1,62853, 'Sen''jin'),
(17,62785,1,62853, 'Thunder Bluff'),
(17,62786,1,62853, 'Silvermoon'),
(17,62787,1,62853, 'Undercity'),
(17,62774,1,62853, 'Stormwind'),
(17,62779,1,62853, 'Ironforge'),
(17,62780,1,62853, 'Gnomregan'),
(17,62781,1,62853, 'Exodar'),
(17,62782,1,62853, 'Darnassus');
--  SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED         = 60, // You must have a lance equipped.

-- Quests Valiant of ... - after player has completed Champion Rises for his faction
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (19,20) AND `SourceEntry` IN (13593,13703,13704,13705,13706,13707,13708,13709,13710,13711) AND `ConditionTypeOrReference`=14;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(19,0,13593,0,14,13686,0,0,0,'','Valiant Of Stormwind - Alliance Tournament Eligibility Marker'),
(19,0,13703,0,14,13686,0,0,0,'','Valiant Of Ironforge - Alliance Tournament Eligibility Marker'),
(19,0,13704,0,14,13686,0,0,0,'','Valiant Of Gnomeregan - Alliance Tournament Eligibility Marker'),
(19,0,13705,0,14,13686,0,0,0,'','Valiant Of The Exodar - Alliance Tournament Eligibility Marker'),
(19,0,13706,0,14,13686,0,0,0,'','Valiant Of Darnassus - Alliance Tournament Eligibility Marker'),
(19,0,13707,0,14,13687,0,0,0,'','Valiant Of Orgrimmar - Horde Tournament Eligibility Marker'),
(19,0,13708,0,14,13687,0,0,0,'','Valiant Of Sen''jin - Horde Tournament Eligibility Marker'),
(19,0,13709,0,14,13687,0,0,0,'','Valiant Of Thunder Bluff - Horde Tournament Eligibility Marker'),
(19,0,13710,0,14,13687,0,0,0,'','Valiant Of Undercity - Horde Tournament Eligibility Marker'),
(19,0,13711,0,14,13687,0,0,0,'','Valiant Of Silvermoon - Horde Tournament Eligibility Marker'),
(20,0,13593,0,14,13686,0,0,0,'','Valiant Of Stormwind - Alliance Tournament Eligibility Marker'),
(20,0,13703,0,14,13686,0,0,0,'','Valiant Of Ironforge - Alliance Tournament Eligibility Marker'),
(20,0,13704,0,14,13686,0,0,0,'','Valiant Of Gnomeregan - Alliance Tournament Eligibility Marker'),
(20,0,13705,0,14,13686,0,0,0,'','Valiant Of The Exodar - Alliance Tournament Eligibility Marker'),
(20,0,13706,0,14,13686,0,0,0,'','Valiant Of Darnassus - Alliance Tournament Eligibility Marker'),
(20,0,13707,0,14,13687,0,0,0,'','Valiant Of Orgrimmar - Horde Tournament Eligibility Marker'),
(20,0,13708,0,14,13687,0,0,0,'','Valiant Of Sen''jin - Horde Tournament Eligibility Marker'),
(20,0,13709,0,14,13687,0,0,0,'','Valiant Of Thunder Bluff - Horde Tournament Eligibility Marker'),
(20,0,13710,0,14,13687,0,0,0,'','Valiant Of Undercity - Horde Tournament Eligibility Marker'),
(20,0,13711,0,14,13687,0,0,0,'','Valiant Of Silvermoon - Horde Tournament Eligibility Marker');

-- Breakfast Of Champions
UPDATE`gameobject_template`SET`ScriptName`='go_mysterious_snow_mound' WHERE`entry`IN(195308,195309);
REPLACE INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES 
(34920,46889,-100,1,0,1,1);

-- What Do You Feed a Yeti, Anyway?
UPDATE creature_template SET faction=14,unit_flags=unit_flags|0x8000 WHERE entry IN (35072); -- Angry Kvaldir
UPDATE creature_template SET faction=14,InhabitType=2,unit_flags=unit_flags|0x8000 WHERE entry IN (35071,35060,35061); -- sharks
-- 0x8000 UNIT_FLAG_UNK_15  = swimming

-- The Black Knight's Orders
UPDATE `creature_template` SET InhabitType=7,`ScriptName`='vehicle_knight_gryphon' WHERE `entry`=33519;
DELETE FROM `gameobject` WHERE `guid`=300007 AND `id`=300007;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(300007,300007,571,1,1,8523.51,566.994,552.841,2.1518,0,0,0.880019,0.474938,300,0,1);

-- See black knight's invisibility while on quest The Black Knight's Orders
DELETE FROM `spell_area` WHERE `spell`=67471 AND `area` IN (4658);
INSERT INTO `spell_area` (`spell`,`area`,`quest_start`,`quest_end`,`aura_spell`,`racemask`,`gender`,`autocast`) VALUES
(67471,4658,13663,13663,0,0,2,1); -- See Black Knight Invis

-- The Black Knight's Fall
UPDATE `creature_template` SET `scriptname`='npc_black_knight_argent' WHERE `entry`=33785;
UPDATE `creature_template` SET `scriptname`='npc_squire_cavin' WHERE `entry`=33522;
DELETE FROM `creature` WHERE `id`=33870;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(3387000,33870,571,1,1,0,8484.49,910.085,547.293,2.77386,300,0,0,50000,0,0,0,0,0);
 

-- The Black Knight's Curse --
-- Support for quest The Black Knight's Curse (14016)
-- Black Knight's Grave (34735)

-- need to activate only when on quest ... perhaps Generic Quest Invisibility 2 49415 + Generic Quest Invisibility Detection 2 49417
-- !!hack!!
UPDATE`creature_addon`SET`auras`='67549 49415' WHERE`guid`=88078; -- 67549
DELETE FROM `spell_area` WHERE `spell`=49417 AND `area` IN (4658);
INSERT INTO `spell_area` (`spell`,`area`,`quest_start`,`quest_end`,`aura_spell`,`racemask`,`gender`,`autocast`) VALUES
(49417,4658,14016,1,0,0,2,1); -- See Black Knight Invis

UPDATE creature_template SET AIName='EventAI', flags_extra=flags_extra|130 WHERE entry=34735;

UPDATE `creature_template` SET AIName='EventAI'  WHERE entry=35116;

-- INSERT IGNORE INTO creature_equip_template VALUES (3334,1195,0,0); -- probably incorrect

-- Add texts, EventAi and small changes for Cult Assassin (35127)
-- EventAi

UPDATE `creature_template` SET AIName='EventAI' WHERE entry=35127; -- Cult Assassin - eq id not correct

-- UPDATE `creature_template` SET `faction_A`=7,`faction_H`=7 WHERE `entry` IN (35116,35127);

-- Add conditions (SPELL_SCRIPT_TARGET) to spell 48028 (uses TARGET_UNIT_AREA_ENTRY_SRC)
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=66785;
INSERT INTO `conditions`
(`SourceTypeOrReferenceId`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`Comment`) VALUES
(13,66785,0,18,1,0,'Black Knights Grave Credit cast on players');
-- The Black Knight's Curse -- end --

-- You've Really Done It This Time, Kul
UPDATE gameobject SET state=1 WHERE guid IN (61663,61683); -- It looks stupid when prisoner is sitting in an open cage
UPDATE gameobject_template SET data2=180*1000 WHERE entry=195310; -- 180s to auto close ... was 0

-- Horde ArgentTournament
    -- Daily Aspirant Quests -- all values were 0
UPDATE `quest_template` SET `PrevQuestId`=-13678, `ExclusiveGroup`=13673 WHERE `ID`=13673; -- A Blade Fit For A Champion
UPDATE `quest_template` SET `PrevQuestId`=-13678, `ExclusiveGroup`=13673 WHERE `ID`=13675; -- The Edge Of Winter
UPDATE `quest_template` SET `PrevQuestId`=-13678, `ExclusiveGroup`=13673 WHERE `ID`=13674; -- A Worthy Weapon
UPDATE `quest_template` SET `PrevQuestId`=-13678, `ExclusiveGroup`=0 WHERE `ID`=13676;
UPDATE `quest_template` SET `PrevQuestId`=-13678, `ExclusiveGroup`=0 WHERE `ID`=13677;
-- "A Valiant Of ..."  (13691, 13693, 13694, 13695, 13696)
UPDATE `quest_template` SET `NextQuestId`=13697, `ExclusiveGroup`=13691 WHERE `ID`=13691;
UPDATE `quest_template` SET `NextQuestId`=13719, `ExclusiveGroup`=13693 WHERE `ID`=13693;
UPDATE `quest_template` SET `NextQuestId`=13720, `ExclusiveGroup`=13694 WHERE `ID`=13694;
UPDATE `quest_template` SET `NextQuestId`=13721, `ExclusiveGroup`=13695 WHERE `ID`=13695;
UPDATE `quest_template` SET `NextQuestId`=13722, `ExclusiveGroup`=13696 WHERE `ID`=13696;

-- "Valiant Of ..." (13707, 13708, 13709, 13710, 13711)
UPDATE `quest_template` SET `NextQuestId`=13697, `ExclusiveGroup`=13691 WHERE `ID`=13707;
UPDATE `quest_template` SET `NextQuestId`=13719, `ExclusiveGroup`=13693 WHERE `ID`=13708;
UPDATE `quest_template` SET `NextQuestId`=13720, `ExclusiveGroup`=13694 WHERE `ID`=13709;
UPDATE `quest_template` SET `NextQuestId`=13721, `ExclusiveGroup`=13695 WHERE `ID`=13710;
UPDATE `quest_template` SET `NextQuestId`=13722, `ExclusiveGroup`=13696 WHERE `ID`=13711;

UPDATE `quest_template` SET `PrevQuestId`=0 WHERE `ID` IN (13697, 13719, 13720, 13721, 13722); -- The Valiant's Charge (was id of corresponding A Valiant Of ...)

    -- Valiant Daily Quests
        -- A Blade Fit For A Champion
        -- The Edge Of Winter
        -- A Worthy Weapon
UPDATE `quest_template` SET `PrevQuestId`=-13697, `ExclusiveGroup`=13762, `RequiredRaces`=690 WHERE `ID` IN (13762, 13763, 13764); -- was 13687,0, requiredraces was set to one race only
UPDATE `quest_template` SET `PrevQuestId`=-13719, `ExclusiveGroup`=13768, `RequiredRaces`=690 WHERE `ID` IN (13768, 13769, 13770);
UPDATE `quest_template` SET `PrevQuestId`=-13720, `ExclusiveGroup`=13773, `RequiredRaces`=690 WHERE `ID` IN (13773, 13774, 13775);
UPDATE `quest_template` SET `PrevQuestId`=-13721, `ExclusiveGroup`=13778, `RequiredRaces`=690 WHERE `ID` IN (13778, 13779, 13780);
UPDATE `quest_template` SET `PrevQuestId`=-13722, `ExclusiveGroup`=13783, `RequiredRaces`=690 WHERE `ID` IN (13783, 13784, 13785);
        -- A Valiant's Field Training
        -- The Grand Melee
        -- At The Enemy's Gates
UPDATE `quest_template` SET `PrevQuestId`=-13697, `RequiredRaces`=690 WHERE `ID` IN (13765, 13767, 13856); -- was 13687, requiredraces was set to one race only
UPDATE `quest_template` SET `PrevQuestId`=-13719, `RequiredRaces`=690 WHERE `ID` IN (13771, 13772, 13857);
UPDATE `quest_template` SET `PrevQuestId`=-13720, `RequiredRaces`=690 WHERE `ID` IN (13776, 13777, 13858);
UPDATE `quest_template` SET `PrevQuestId`=-13721, `RequiredRaces`=690 WHERE `ID` IN (13781, 13782, 13860);
UPDATE `quest_template` SET `PrevQuestId`=-13722, `RequiredRaces`=690 WHERE `ID` IN (13786, 13787, 13859);

-- Debug Quest Requirements - no RequiredRaces need to be set IMO (only one race was set for each quest)
UPDATE `quest_template` SET `RequiredRaces`=690 WHERE `ID` IN (13697,13719,13720,13721,13722);  -- The Valiant's Charge
UPDATE `quest_template` SET `RequiredRaces`=690 WHERE `ID` IN (13726,13727,13728,13729,13731);  -- The Valiant's Challenge

-- Alliance ArgentTournament
    -- Daily Aspirant Quests -- all values were 0
UPDATE `quest_template` SET `PrevQuestId`=-13672, `ExclusiveGroup`=13666 WHERE `ID`=13666; -- A Blade Fit For A Champion
UPDATE `quest_template` SET `PrevQuestId`=-13672, `ExclusiveGroup`=13666 WHERE `ID`=13670; -- The Edge Of Winter
UPDATE `quest_template` SET `PrevQuestId`=-13672, `ExclusiveGroup`=13666 WHERE `ID`=13669; -- A Worthy Weapon
UPDATE `quest_template` SET `PrevQuestId`=-13672, `ExclusiveGroup`=0 WHERE `ID`=13671;
UPDATE `quest_template` SET `PrevQuestId`=-13672, `ExclusiveGroup`=0 WHERE `ID`=13625;
-- "A Valiant Of ..."   (13684, 13685, 13689, 13688, 13690)
UPDATE `quest_template` SET `NextQuestId`=13718, `ExclusiveGroup`=13684 WHERE `ID`=13684;
UPDATE `quest_template` SET `NextQuestId`=13714, `ExclusiveGroup`=13685 WHERE `ID`=13685;
UPDATE `quest_template` SET `NextQuestId`=13717, `ExclusiveGroup`=13689 WHERE `ID`=13689;
UPDATE `quest_template` SET `NextQuestId`=13715, `ExclusiveGroup`=13688 WHERE `ID`=13688;
UPDATE `quest_template` SET `NextQuestId`=13716, `ExclusiveGroup`=13690 WHERE `ID`=13690;
-- "Valiant Of ..." (13593, 13703, 13706, 13704, 13705)
UPDATE `quest_template` SET `NextQuestId`=13718, `ExclusiveGroup`=13718 WHERE `ID`=13593;
UPDATE `quest_template` SET `NextQuestId`=13714, `ExclusiveGroup`=13714 WHERE `ID`=13703;
UPDATE `quest_template` SET `NextQuestId`=13717, `ExclusiveGroup`=13717 WHERE `ID`=13706;
UPDATE `quest_template` SET `NextQuestId`=13715, `ExclusiveGroup`=13715 WHERE `ID`=13704;
UPDATE `quest_template` SET `NextQuestId`=13716, `ExclusiveGroup`=13716 WHERE `ID`=13705;

UPDATE `quest_template` SET `PrevQuestId`=0 WHERE `ID` IN (13718, 13714, 13717, 13715, 13716); -- The Valiant's Charge (was id of corresponding A Valiant Of ...)

    -- Valiant Daily Quests
        -- A Blade Fit For A Champion
        -- The Edge Of Winter
        -- A Worthy Weapon
UPDATE `quest_template` SET `PrevQuestId`=-13718, `ExclusiveGroup`=13603, `RequiredRaces`=1101 WHERE `ID` IN (13603, 13600, 13616); -- prevquestid was 13686, requiredraces was set to one race only
UPDATE `quest_template` SET `PrevQuestId`=-13714, `ExclusiveGroup`=13741, `RequiredRaces`=1101 WHERE `ID` IN (13741, 13742, 13743);
UPDATE `quest_template` SET `PrevQuestId`=-13717, `ExclusiveGroup`=13757, `RequiredRaces`=1101 WHERE `ID` IN (13757, 13758, 13759);
UPDATE `quest_template` SET `PrevQuestId`=-13715, `ExclusiveGroup`=13746, `RequiredRaces`=1101 WHERE `ID` IN (13746, 13747, 13748);
UPDATE `quest_template` SET `PrevQuestId`=-13716, `ExclusiveGroup`=13752, `RequiredRaces`=1101 WHERE `ID` IN (13752, 13753, 13754);
        -- A Valiant's Field Training
        -- The Grand Melee
        -- At The Enemy's Gates
UPDATE `quest_template` SET `PrevQuestId`=-13718, `RequiredRaces`=1101 WHERE `ID` IN (13592, 13665, 13847); -- prevquestid was 13686, requiredraces was set to one race only
UPDATE `quest_template` SET `PrevQuestId`=-13714, `RequiredRaces`=1101 WHERE `ID` IN (13744, 13745, 13851);
UPDATE `quest_template` SET `PrevQuestId`=-13717, `RequiredRaces`=1101 WHERE `ID` IN (13760, 13761, 13855);
UPDATE `quest_template` SET `PrevQuestId`=-13715, `RequiredRaces`=1101 WHERE `ID` IN (13749, 13750, 13852);
UPDATE `quest_template` SET `PrevQuestId`=-13716, `RequiredRaces`=1101 WHERE `ID` IN (13755, 13756, 13854);

-- Debug Quest Requirements - no RequiredRaces need to be set IMO (only one race was set for each quest)
UPDATE `quest_template` SET `RequiredRaces`=1101 WHERE `ID` IN (13718,13714,13717,13715,13716); -- The Valiant's Charge
UPDATE `quest_template` SET `RequiredRaces`=1101 WHERE `ID` IN (13699,13713,13725,13723,13724); -- The Valiant's Challenge