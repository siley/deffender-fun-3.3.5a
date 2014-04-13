-- Create table
CREATE TABLE `custom_transmogrification` (
        `GUID` INT(10) UNSIGNED NOT NULL DEFAULT '0',
        `FakeEntry` INT(10) UNSIGNED NOT NULL DEFAULT '0',
        PRIMARY KEY (`GUID`)
)
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;