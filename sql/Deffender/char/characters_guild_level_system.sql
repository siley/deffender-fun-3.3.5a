ALTER TABLE `guild` ADD `xp` INT(10) DEFAULT 0 NOT NULL AFTER `BankMoney`;
ALTER TABLE `guild` ADD `level` TINYINT(3) DEFAULT 0 NOT NULL AFTER `xp`;

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `guild_bonus_config`
-- ----------------------------
DROP TABLE IF EXISTS `guild_bonus_config`;
CREATE TABLE `guild_bonus_config` (
  `BonusId` smallint(5) NOT NULL DEFAULT '0',
  `RequiredGuildLevel` tinyint(3) NOT NULL DEFAULT '0',
  `comment` longtext CHARACTER SET utf8
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of guild_bonus_config
-- ----------------------------
INSERT INTO `guild_bonus_config` VALUES ('1', '4', 'Goldbonus | 5% Bonus gold for the guild bank');
INSERT INTO `guild_bonus_config` VALUES ('2', '1', 'XP-Bonus | +5% XP at the end of quest or kill monsters');
INSERT INTO `guild_bonus_config` VALUES ('3', '2', 'Faster Spirit | Double movement speed as spirit');
INSERT INTO `guild_bonus_config` VALUES ('4', '6', 'Cheap repair | -25% Repair costs');
INSERT INTO `guild_bonus_config` VALUES ('5', '11', 'Goldbonus-2 | 10% Bonus gold for the guild bank');
INSERT INTO `guild_bonus_config` VALUES ('6', '5', 'Riding Pace | +5% Riding pace (Except Battlegrounds and Arenas)');
INSERT INTO `guild_bonus_config` VALUES ('7', '3', 'Good Relationships | +5% Reputation gain');
INSERT INTO `guild_bonus_config` VALUES ('8', '4', 'XP-Bonus-2 | +10% XP at the end of quest or kill monsters');
INSERT INTO `guild_bonus_config` VALUES ('9', '12', 'Cheap Repair-2 | -50% Repair costs');
INSERT INTO `guild_bonus_config` VALUES ('10', '11', 'Riding Pace-2 | +10% Riding pace (Except Battlegrounds and Arenas)');
INSERT INTO `guild_bonus_config` VALUES ('11', '8', 'Good Relationships-2 | +10% Reputation gain');
INSERT INTO `guild_bonus_config` VALUES ('12', '7', 'Bonus Honor | +5% Honor');
INSERT INTO `guild_bonus_config` VALUES ('13', '8', 'Bonus Honor-2 | +10% Honor');
INSERT INTO `guild_bonus_config` VALUES ('14', '9', 'Guild Mail | 50% faster Mail');
INSERT INTO `guild_bonus_config` VALUES ('15', '16', 'Guild Mail-2 | Instant Mail');
INSERT INTO `guild_bonus_config` VALUES ('16', '10', 'flashk by 100%');
INSERT INTO `guild_bonus_config` VALUES ('17', '15', 'Cheap Repair-3 | -75% Repair costs');
INSERT INTO `guild_bonus_config` VALUES ('18', '13', 'Mobile Guild Vault');
INSERT INTO `guild_bonus_config` VALUES ('19', '14', 'Mount ground + fly');
INSERT INTO `guild_bonus_config` VALUES ('20', '16', 'Mount ground/fly');

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `guild_xp_for_next_level`
-- ----------------------------
DROP TABLE IF EXISTS `guild_xp_for_next_level`;
CREATE TABLE `guild_xp_for_next_level` (
  `level` tinyint(3) NOT NULL DEFAULT '0',
  `xp_for_next_level` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of guild_xp_for_next_level
-- ----------------------------
INSERT INTO `guild_xp_for_next_level` VALUES ('0', '8000000');
INSERT INTO `guild_xp_for_next_level` VALUES ('1', '12000000');
INSERT INTO `guild_xp_for_next_level` VALUES ('2', '18000000');
INSERT INTO `guild_xp_for_next_level` VALUES ('3', '27000000');
INSERT INTO `guild_xp_for_next_level` VALUES ('4', '40500000');
INSERT INTO `guild_xp_for_next_level` VALUES ('5', '60750000');
INSERT INTO `guild_xp_for_next_level` VALUES ('6', '85125000');
INSERT INTO `guild_xp_for_next_level` VALUES ('7', '110687500');
INSERT INTO `guild_xp_for_next_level` VALUES ('8', '136645500');
INSERT INTO `guild_xp_for_next_level` VALUES ('9', '160087500');
INSERT INTO `guild_xp_for_next_level` VALUES ('10', '185107500');
INSERT INTO `guild_xp_for_next_level` VALUES ('11', '205000000');
INSERT INTO `guild_xp_for_next_level` VALUES ('12', '235727500');
INSERT INTO `guild_xp_for_next_level` VALUES ('13', '270870000');
INSERT INTO `guild_xp_for_next_level` VALUES ('14', '300985000');
INSERT INTO `guild_xp_for_next_level` VALUES ('15', '350000000');
