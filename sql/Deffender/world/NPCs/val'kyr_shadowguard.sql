-- Fix Val'kyr Shadowguard speed
UPDATE `creature_template` SET `speed_walk` = '0.642857' WHERE `entry` IN (36609, 39120, 39121, 39122);