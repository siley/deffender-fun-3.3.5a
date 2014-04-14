DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=51722 AND `spell_effect`=-46924 ;
DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=676 AND `spell_effect`=-46924;
INSERT INTO `spell_linked_spell` VALUES (676, -46924, 1, '(War)Disarm Cancel Bladestorm');
INSERT INTO `spell_linked_spell` VALUES (51722, -46924, 1, '(Rogue)Dismantle Cancel Bladestorm');
INSERT INTO `spell_linked_spell` VALUES (64058, -46924, 1, '(Priest) Psychic Horror Cancel Bladestorm');
DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=64346 AND `spell_effect`=-46924;
INSERT INTO `spell_linked_spell` VALUES (64346, -46924, 1, '(Mage)Fiery Payback Cancel Bladestorm');
DELETE FROM `spell_linked_spell` WHERE  `spell_trigger`=53359 AND `spell_effect`=-46924;
INSERT INTO `spell_linked_spell` VALUES (53359, -46924, 1, '(Hunter)Chimera Shot(scorpid) Cancel Bladestorm');
