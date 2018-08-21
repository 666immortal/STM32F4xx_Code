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
#ifndef _BEEP_H_
#define _BEEP_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
//#define LED0        0
//#define LED1        1

//#define LED_OFF     0
//#define LED_ON      1


/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitBeep(void);                    //初始化LED模块
void  BeepToogle(u16 cnt);              //cnt为250时表示500毫秒更改一次LED状态

#endif

