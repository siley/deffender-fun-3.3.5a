ALTER TABLE `creature_respawn`
MODIFY COLUMN `guid`  bigint(64) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' FIRST ;
ALTER TABLE `gameobject_respawn`
MODIFY COLUMN `guid`  bigint(64) UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Global Unique Identifier' FIRST ;