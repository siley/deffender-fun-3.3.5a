DROP TABLE IF EXISTS `players_reports_status`;

CREATE TABLE `players_reports_status` (
  `guid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `creation_time` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `average` FLOAT NOT NULL DEFAULT '0',
  `total_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `speed_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `fly_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `jump_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `waterwalk_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `teleportplane_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `climb_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='';

DROP TABLE IF EXISTS `daily_players_reports`;

CREATE TABLE `daily_players_reports` (
  `guid` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `creation_time` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `average` FLOAT NOT NULL DEFAULT '0',
  `total_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `speed_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `fly_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `jump_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `waterwalk_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `teleportplane_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  `climb_reports` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='';

INSERT INTO `command` VALUES ('anticheat global', 2, 'Syntax: .anticheat global returns the total amount reports and the average. (top three players)');
INSERT INTO `command` VALUES ('anticheat player', 2, 'Syntax: .anticheat player $name returns the players\'s total amount of warnings, the average and the amount of each cheat type.');
INSERT INTO `command` VALUES ('anticheat handle', 2, 'Syntax: .anticheat handle [on|off] Turn on/off the AntiCheat-Detection .');
INSERT INTO `command` VALUES ('anticheat delete', 2, 'Syntax: .anticheat delete [deleteall|$name] Deletes the report records of all the players or deletes all the reports of player $name.');
