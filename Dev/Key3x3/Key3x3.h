﻿/*********************************************************************************************************
* 模块名称: Key4x4.h
* 摘    要: 
* 当前版本: 1.0.0
* 作    者: 
* 完成日期: 
* 内    容:
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 
* 作    者:
* 完成日期: 
* 修改内容:
* 修改文件: 
*********************************************************************************************************/
#ifndef _KEY_4X4_H_
#define _KEY_4X4_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitKey3x3(void);       //初始化Key3x3
u8 ScanKey3x3(void);          //按键扫描，2ms扫描一次
u8 GetKey3x3(void);           //通过列-行按键值获取键值

#endif


