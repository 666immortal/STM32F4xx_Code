﻿/*********************************************************************************************************
* 模块名称: LED.h
* 摘    要: LED模块，包含LED模块初始化以及LED闪烁函数
* 当前版本: 1.0.0
* 作    者: SZLY(COPYRIGHT 2018 SZLY. All rights reserved.)
* 完成日期: 2018年01月01日 
* 内    容:
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/
#ifndef _LED_H_
#define _LED_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define USER_DEFINE_LED_GPIO_PORT   GPIOC                    //用户定义LED的GPIO端口                                                             
#define USER_DEFINE_LED_GPIO_PIN    GPIO_Pin_13              //用户定义LED的引脚                                                             
#define USER_DEFINE_LED_GPIO_CLK    RCC_AHB1Periph_GPIOC     //用户定义LED的时钟

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitLED(void);                    //初始化LED
void  LEDFlicker(u16 cnt);              //LED闪烁

#endif
