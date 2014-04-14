
UPDATE `creature_template` SET `npcflag`='2' WHERE (`entry`='38606');  
UPDATE `creature_template` SET `npcflag`='2' WHERE (`entry`='38607'); 
UPDATE `creature_template` SET `npcflag`='2' WHERE (`entry`='38608');
UPDATE `creature_template` SET `npcflag`='2' WHERE (`entry`='38609');
 
UPDATE `creature_queststarter` SET `id`=38606 WHERE `id`=37120 AND `quest`=24916; -- Lady Jaina Proudmoore - Jaina's Locket
UPDATE `creature_queststarter` SET `id`=38607 WHERE `id`=37120 AND `quest`=24917; -- Muradin Bronzebeard - Muradin's Lament
UPDATE `creature_queststarter` SET `id`=38608 WHERE `id`=37120 AND `quest`=24919; -- Uther the Lightbringer - The Lightbringer's Redemption
UPDATE `creature_queststarter` SET `id`=38609 WHERE `id`=37120 AND `quest`=24918; -- Lady Sylvanas Windrunner - Sylvanas' Vengeance

UPDATE `creature_questender` SET `id`=38606 WHERE `id`=37120 AND `quest`=24916; -- Lady Jaina Proudmoore - Jaina's Locket
UPDATE `creature_questender` SET `id`=38607 WHERE `id`=37120 AND `quest`=24917; -- Muradin Bronzebeard - Muradin's Lament
UPDATE `creature_questender` SET `id`=38608 WHERE `id`=37120 AND `quest`=24919; -- Uther the Lightbringer - The Lightbringer's Redemption
UPDATE `creature_questender` SET `id`=38609 WHERE `id`=37120 AND `quest`=24918; -- Lady Sylvanas Windrunner - Sylvanas' Vengeance

DELETE FROM `creature_queststarter` WHERE `id`=37120 AND `quest`=24912;
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES
(37120, 24912); -- Highlord Darion Mograine - Empowerment

DELETE FROM `creature_questender` WHERE `id`=37120 AND `quest`=24912;
INSERT INTO `creature_questender` (`id`,`quest`) VALUES
(37120, 24912); -- Highlord Darion Mograine - Empowerment

UPDATE `quest_template` SET `NextQuestId`=24912 WHERE `Id`=24548; -- The Splintered Throne
UPDATE `quest_template` SET `PrevQuestId`=24548, `NextQuestId`=24549, `OfferRewardText`='Stand Clear, $c, and steady yourself.', `RequestItemsText`='<Highlord Darion Mograine speaks to you purposefully.>$B$BShadow''s Edge is prepared to receive its final endowment of power.$B$BThe time has come to attempt the forging of Shadowmourne!' WHERE `Id`=24912; -- Empowerment
UPDATE `quest_template` SET `PrevQuestId`=24912 WHERE `Id`=24549; -- Shadowmourne...

-- Remove unneeded SAI script
UPDATE `creature_template` SET `AIName`='' WHERE `entry`=37120;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=37120 AND `source_type`=0 AND `id`=0 AND `link`=0;

-- Fix Sylvanas Music Box
DELETE FROM spell_script_names WHERE spell_id = 73331;
INSERT INTO spell_script_names VALUES ('73331', 'spell_item_sylvanas_music_box');

-- Upd HoR Lich King immunes
UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask`|1|2|4|8|16|32|64|256|512|1024|2048|4096|8192|65536|131072|524288|4194304|8388608|33554432|67108864|536870912 WHERE `entry` IN (36954);