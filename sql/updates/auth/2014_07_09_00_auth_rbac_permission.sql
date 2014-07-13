SET @id = 631;

-- Add new permissions
DELETE FROM `fun_permissions` WHERE `id`=@id;
INSERT INTO `fun_permissions` (`id`, `name`) VALUES
(@id, 'Command: reload battleground_template');

DELETE FROM `fun_linked_permissions` WHERE `linkedId`=@id;
INSERT INTO `fun_linked_permissions` (`id`, `linkedId`) VALUES
(196, @id);
