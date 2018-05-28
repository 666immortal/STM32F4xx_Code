﻿/*********************************************************************************************************
* 模块名称: I2C.h
* 摘    要: I2C驱动
* 当前版本: 1.0.0
* 作    者: SZLY(COPYRIGHT 2018 SZLY. All rights reserved.)
* 完成日期: 2018年03月01日
* 内    容:
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/
#ifndef _I2C_H_  
#define _I2C_H_  

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include <stm32f4xx_conf.h>
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define USER_DEFINE_I2C_SCL_GPIO_PORT     GPIOH                      //用户定义I2C.SCL的GPIO端口
#define USER_DEFINE_I2C_SCL_GPIO_PIN      GPIO_Pin_4                 //用户定义I2C.SCL的引脚
#define USER_DEFINE_I2C_SCL_GPIO_CLK      RCC_AHB1Periph_GPIOH       //用户定义I2C.SCL的时钟

#define USER_DEFINE_I2C_SDA_GPIO_PORT     GPIOH                      //用户定义I2C.SDA的GPIO端口
#define USER_DEFINE_I2C_SDA_GPIO_PIN      GPIO_Pin_5                 //用户定义I2C.SDA的引脚
#define USER_DEFINE_I2C_SDA_GPIO_CLK      RCC_AHB1Periph_GPIOH       //用户定义I2C.SDA的时钟

/*********************************************************************************************************
*                                              结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitI2C(void);            //初始化IIC，主要是GPIO的初始化
  
void  GenI2CStartSig(void);     //产生IIC起始时序
void  GenI2CStopSig(void);      //产生IIC停止时序

void  I2CSendByte(u8 txd);      //IIC发送一个字节
u8    I2CReadByte(u8 ack);      //IIC读取一个字节

u8    I2CWaitAck(void);         //IIC等待ACK信号

void  SendI2CAck(void);         //IIC发送ACK信号
void  SendI2CNAck(void);        //IIC不发送ACK信号

#endif
