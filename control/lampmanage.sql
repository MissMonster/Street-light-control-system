/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50051
Source Host           : localhost:3306
Source Database       : lampmanage

Target Server Type    : MYSQL
Target Server Version : 50051
File Encoding         : 65001

Date: 2015-04-21 14:56:43
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_controllerinfo`
-- ----------------------------
DROP TABLE IF EXISTS `t_controllerinfo`;
CREATE TABLE `t_controllerinfo` (
  `controllerId` varchar(255) NOT NULL COMMENT '控制器标识码',
  `controllerInfo` varchar(255) default NULL COMMENT '控制器信息',
  `controllerLongitude` float NOT NULL COMMENT '控制器经度坐标',
  `controllerLatitude` float NOT NULL COMMENT '控制器纬度坐标',
  `streetlightNum` int(11) NOT NULL COMMENT '路灯数量',
  `controllerAutorun` int(11) NOT NULL COMMENT '运行方式',
  `voltageThreadholdHigh` int(11) default NULL COMMENT '电压上限值',
  `voltageThreadholdLow` int(11) default NULL COMMENT '电压下限值',
  `currentThreadholdHigh` int(11) default NULL COMMENT '电流上限值',
  `currentThreadholdLow` int(11) default NULL COMMENT '电流下限值',
  `tempThreadholdHigh` int(11) default NULL COMMENT '温度上限值',
  `tempThreadholdLow` int(11) default NULL COMMENT '温度下限值',
  `controllerWarning` char(255) default NULL COMMENT '故障情况',
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
  `id` int(11) NOT NULL COMMENT '序号',
  `deviceType` varchar(255) NOT NULL COMMENT '传感器类型',
  `deviceId` varchar(255) NOT NULL COMMENT '传感器标识码',
  `deviceInfo` varchar(255) default NULL COMMENT '传感器信息',
  `value` varchar(255) default NULL COMMENT '实时监测值',
  `deviceLatitude` float default NULL COMMENT '传感器纬度坐标',
  `deviceLongitude` float default NULL COMMENT '传感器经度坐标',
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
  `id` int(11) NOT NULL COMMENT '序号',
  `time` datetime default NULL COMMENT '故障发生时间',
  `deviceType` varchar(255) default NULL COMMENT '故障设备类型',
  `controllerId` varchar(255) default NULL COMMENT '控制器标识码',
  `streetlightId` int(11) default NULL COMMENT '路灯编号',
  `errorType` char(255) default NULL COMMENT '错误类型',
  `lightVoltage` varchar(255) default NULL COMMENT '路灯电压',
  `lightCurrent` varchar(255) default NULL COMMENT '路灯电流',
  `lightTemp` varchar(255) default NULL COMMENT '路灯温度',
  `latitude` float default NULL COMMENT '纬度坐标',
  `longitude` float default NULL COMMENT '经度坐标',
  `errorMsg` varchar(255) default NULL COMMENT '故障信息',
  `autoWarned` varchar(255) default NULL COMMENT '自动提示',
  `processed` varchar(255) default NULL COMMENT '处理情况',
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
  `id` int(11) NOT NULL COMMENT '序号',
  `controllerId` varchar(255) NOT NULL COMMENT '控制器标识码',
  `streetlightId` int(11) default NULL COMMENT '路灯编号',
  `streetlightLongitude` float default NULL COMMENT '路灯经度坐标',
  `streetlightLatitude` float default NULL COMMENT '路灯纬度坐标',
  `streetlightVoltage` varchar(255) default NULL COMMENT '路灯实时电压',
  `streetlightCurrent` varchar(255) default NULL COMMENT '路灯实时电流',
  `streetlightTemp` varchar(255) default NULL COMMENT '路灯实时温度',
  `streetlightBrightness` varchar(255) default NULL COMMENT '路灯实时亮度',
  `streetlightSet` varchar(255) default NULL COMMENT '设置亮度',
  `streetlightWarning` varchar(255) default NULL COMMENT '路灯故障情况',
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
  `id` int(11) NOT NULL COMMENT '序号',
  `startDate` datetime NOT NULL COMMENT '开始日期',
  `endDate` datetime NOT NULL COMMENT '结束日期',
  `sunriseTime` datetime NOT NULL COMMENT '日出时刻',
  `sunsetTime` datetime NOT NULL COMMENT '日落时刻',
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
  `UserName` varchar(255) NOT NULL COMMENT '用户名',
  `Password` varchar(255) NOT NULL COMMENT '用户密码',
  PRIMARY KEY  (`UserName`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of t_userinfo
-- ----------------------------
INSERT INTO `t_userinfo` VALUES ('admin', '111');
