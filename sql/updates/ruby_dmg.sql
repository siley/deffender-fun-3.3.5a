-- saviana ragefire dmg

UPDATE `creature_template` SET `mindmg`='351',`maxdmg`='526',`attackpower`='132' WHERE (`entry`='39747');  
UPDATE `creature_template` SET `dmg_multiplier`='74' WHERE (`entry`='39747');  
UPDATE `creature_template` SET `baseattacktime`='1500',`rangeattacktime`='1500' WHERE (`entry`='39747');  
UPDATE `creature_template` SET `rank`='3' WHERE (`entry`='39747');
UPDATE `creature_template` SET `speed_run`='2.14286' WHERE (`entry`='39823');  
UPDATE `creature_template` SET `rank`='3' WHERE (`entry`='39823');
UPDATE `creature_template` SET `mindmg`='351',`maxdmg`='526',`attackpower`='132',`dmg_multiplier`='112.8',`baseattacktime`='1500',`rangeattacktime`='1500' WHERE (`entry`='39823');

-- halion adds
UPDATE `creature_template` SET `mindmg`='339',`maxdmg`='508',`attackpower`='127',`dmg_multiplier`='77.4',`baseattacktime`='1500',`rangeattacktime`='1500' WHERE (`entry`='40681');  

UPDATE `creature_template` SET `mindmg`='339',`maxdmg`='508',`attackpower`='127',`dmg_multiplier`='116.8',`baseattacktime`='1500',`rangeattacktime`='1500' WHERE (`entry`='40682');  

UPDATE `creature_template` SET `mindmg`='339',`maxdmg`='508',`attackpower`='127',`dmg_multiplier`='77.4',`baseattacktime`='1500',`rangeattacktime`='1500' WHERE (`entry`='40683');     

UPDATE `creature_template` SET `mindmg`='339',`maxdmg`='508',`attackpower`='127',`dmg_multiplier`='116.8',`baseattacktime`='1500',`rangeattacktime`='1500' WHERE (`entry`='40684'); 

-- general zarithrian dmg
UPDATE `creature_template` SET `rank` = 3,`mindmg` = 351,`maxdmg` = 526,`dmgschool` = 0,`attackpower` = 132,`dmg_multiplier` = 74.8,`baseattacktime` = 1500,`rangeattacktime` = 1500 WHERE `creature_template`.`entry` = 39746;
UPDATE `creature_template` SET `mindmg` = 351,`maxdmg` = 526,`dmgschool` = 0,`attackpower` = 132,`dmg_multiplier` = 112.8,`baseattacktime` = 1500,`rangeattacktime` = 1500 WHERE `creature_template`.`entry` = 39805;
 