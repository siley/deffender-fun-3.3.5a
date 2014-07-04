-- Animal Handler
INSERT INTO spell_script_names VALUES (34453, 'spell_hun_animal_handler'), (34454, 'spell_hun_animal_handler');
DELETE FROM `spell_pet_auras` WHERE `aura` = 68361;
INSERT INTO `spell_pet_auras` VALUES
(34453, 1, 0, 68361),
(34454, 1, 0, 68361);

