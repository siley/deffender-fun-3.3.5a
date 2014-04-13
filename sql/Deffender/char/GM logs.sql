/*
SQLyog Community v8.82 
MySQL - 5.5.22-0ubuntu1 : Database - wotlk_fun_characters
*********************************************************************
*/


/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


/*Table structure for table `logy_gm` */

DROP TABLE IF EXISTS `logy_gm`;

CREATE TABLE `logy_gm` (
  `id` int(9) NOT NULL AUTO_INCREMENT,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `player` varchar(12) NOT NULL,
  `account` int(9) NOT NULL,
  `command` varchar(255) NOT NULL,
  `position` varchar(96) NOT NULL,
  `selected` varchar(96) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `account` (`account`),
  KEY `player` (`player`)
) ENGINE=InnoDB AUTO_INCREMENT=864289 DEFAULT CHARSET=latin1;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;