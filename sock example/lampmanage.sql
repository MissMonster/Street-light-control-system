/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50051
Source Host           : localhost:3306
Source Database       : lampmanage

Target Server Type    : MYSQL
Target Server Version : 50051
File Encoding         : 65001

Date: 2015-03-26 14:21:32
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_controllerinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_controllerinfo`;
CREATE TABLE `t_controllerinfo` (
  `controllerId` varchar(255) NOT NULL,
  `controllerInfo` varchar(255) default NULL,
  `controllerLongitude` float NOT NULL,
  `controllerLatitude` float NOT NULL,
  `streetlightNum` int(11) NOT NULL,
  `controllerAutorun` int(11) NOT NULL,
  `voltageThreadholdHigh` int(11) default NULL,
  `voltageThreadholdLow` int(11) default NULL,
  `currentThreadholdHigh` int(11) default NULL,
  `currentThreadholdLow` int(11) default NULL,
  `tempThreadholdHigh` int(11) default NULL,
  `tempThreadholdLow` int(11) default NULL,
  `controllerWarning` char(255) default NULL,
  PRIMARY KEY  (`controllerId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_controllerinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_deviceinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_deviceinfo`;
CREATE TABLE `t_deviceinfo` (
  `id` int(11) NOT NULL,
  `deviceType` varchar(255) NOT NULL,
  `deviceId` varchar(255) NOT NULL,
  `deviceInfo` varchar(255) default NULL,
  `value` varchar(255) default NULL,
  `deviceLatitude` float default NULL,
  `deviceLongitude` float default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_deviceinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_errorinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_errorinfo`;
CREATE TABLE `t_errorinfo` (
  `id` int(11) NOT NULL,
  `time` datetime default NULL,
  `deviceType` varchar(255) default NULL,
  `controllerId` varchar(255) default NULL,
  `streetlightId` int(11) default NULL,
  `errorType` char(255) default NULL,
  `lightVoltage` varchar(255) default NULL,
  `lightCurrent` varchar(255) default NULL,
  `lightTemp` varchar(255) default NULL,
  `latitude` float default NULL,
  `longitude` float default NULL,
  `errorMsg` varchar(255) default NULL,
  `autoWarned` varchar(255) default NULL,
  `processed` varchar(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_errorinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_lightinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_lightinfo`;
CREATE TABLE `t_lightinfo` (
  `id` int(11) NOT NULL,
  `controllerId` varchar(255) NOT NULL,
  `streetlightId` int(11) default NULL,
  `streetlightLongitude` float default NULL,
  `streetlightLatitude` float default NULL,
  `streetlightVoltage` varchar(255) default NULL,
  `streetlightCurrent` varchar(255) default NULL,
  `streetlightTemp` varchar(255) default NULL,
  `streetlightBrightness` varchar(255) default NULL,
  `streetlightSet` varchar(255) default NULL,
  `streetlightWarning` varchar(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_lightinfo
-- ----------------------------

-- ----------------------------
-- Table structure for `t_sunrise`
-- ----------------------------
DROP TABLE IF EXISTS `t_sunrise`;
CREATE TABLE `t_sunrise` (
  `id` int(11) NOT NULL,
  `startDate` datetime NOT NULL,
  `endDate` datetime NOT NULL,
  `sunriseTime` datetime NOT NULL,
  `sunsetTime` datetime NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_sunrise
-- ----------------------------

-- ----------------------------
-- Table structure for `t_userinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_userinfo`;
CREATE TABLE `t_userinfo` (
  `UserName` varchar(255) NOT NULL,
  `Password` varchar(255) NOT NULL,
  PRIMARY KEY  (`UserName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_userinfo
-- ----------------------------
INSERT INTO `t_userinfo` VALUES ('admin', '111');
