--- Add Instance binding to first 2 bosses in RS heroic mods
UPDATE `creature_template` SET `flags_extra`='1' WHERE (`entry`='39920');  
UPDATE `creature_template` SET `flags_extra`='1' WHERE (`entry`='39823'); 
  
UPDATE `creature_template` SET `InhabitType`='7' WHERE `entry` IN (39747,39823,36853,38265,38266,38267); 

UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask`|1|2|4|8|16|32|64|256|512|1024|2048|4096|8192|65536|131072|524288|4194304|8388608|33554432|67108864|536870912 WHERE `entry` IN (39864,39944,39945,39863,39747,39823,40142,40143,40144,40145);