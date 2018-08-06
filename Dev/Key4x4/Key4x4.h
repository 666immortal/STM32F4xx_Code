/*********************************************************************************************************
* 模块名称: Key4x4.h
* 摘    要: 
* 当前版本: 1.0.0
* 作    者: SZLY(COPYRIGHT 2018 SZLY. All rights reserved.)
* 完成日期: 2016年05月07日
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
#define USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PORT      GPIOH                //用户定义矩阵键盘ROW0的GPIO端口
#define USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PIN       GPIO_Pin_6           //用户定义矩阵键盘ROW0的引脚    
#define USER_DEFINE_KEY_MATRIX_ROW0_GPIO_CLK       RCC_AHB1Periph_GPIOH //用户定义矩阵键盘ROW0的时钟
                                                          
#define USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PORT      GPIOG                //用户定义矩阵键盘ROW1的GPIO端口
#define USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PIN       GPIO_Pin_3           //用户定义矩阵键盘ROW1的引脚    
#define USER_DEFINE_KEY_MATRIX_ROW1_GPIO_CLK       RCC_AHB1Periph_GPIOG //用户定义矩阵键盘ROW1的时钟
                                                          
#define USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PORT      GPIOG                //用户定义矩阵键盘ROW2的GPIO端口
#define USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PIN       GPIO_Pin_6           //用户定义矩阵键盘ROW2的引脚    
#define USER_DEFINE_KEY_MATRIX_ROW2_GPIO_CLK       RCC_AHB1Periph_GPIOH //用户定义矩阵键盘ROW2的时钟
                                                         
#define USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PORT      GPIOG                //用户定义矩阵键盘ROW3的GPIO端口
#define USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PIN       GPIO_Pin_7           //用户定义矩阵键盘ROW3的引脚    
#define USER_DEFINE_KEY_MATRIX_ROW3_GPIO_CLK       RCC_AHB1Periph_GPIOG //用户定义矩阵键盘ROW3的时钟
                                                         
#define USER_DEFINE_KEY_MATRIX_COL0_GPIO_PORT      GPIOH                //用户定义矩阵键盘COL0的GPIO端口
#define USER_DEFINE_KEY_MATRIX_COL0_GPIO_PIN       GPIO_Pin_11          //用户定义矩阵键盘COL0的引脚    
#define USER_DEFINE_KEY_MATRIX_COL0_GPIO_CLK       RCC_AHB1Periph_GPIOH //用户定义矩阵键盘COL0的时钟
                                                         
#define USER_DEFINE_KEY_MATRIX_COL1_GPIO_PORT      GPIOH                //用户定义矩阵键盘COL1的GPIO端口
#define USER_DEFINE_KEY_MATRIX_COL1_GPIO_PIN       GPIO_Pin_10          //用户定义矩阵键盘COL1的引脚    
#define USER_DEFINE_KEY_MATRIX_COL1_GPIO_CLK       RCC_AHB1Periph_GPIOH //用户定义矩阵键盘COL1的时钟
                                                         
#define USER_DEFINE_KEY_MATRIX_COL2_GPIO_PORT      GPIOH                //用户定义矩阵键盘COL2的GPIO端口
#define USER_DEFINE_KEY_MATRIX_COL2_GPIO_PIN       GPIO_Pin_9           //用户定义矩阵键盘COL2的引脚    
#define USER_DEFINE_KEY_MATRIX_COL2_GPIO_CLK       RCC_AHB1Periph_GPIOH //用户定义矩阵键盘COL2的时钟
                                                         
#define USER_DEFINE_KEY_MATRIX_COL3_GPIO_PORT      GPIOH                //用户定义矩阵键盘COL3的GPIO端口
#define USER_DEFINE_KEY_MATRIX_COL3_GPIO_PIN       GPIO_Pin_7           //用户定义矩阵键盘COL3的引脚    
#define USER_DEFINE_KEY_MATRIX_COL3_GPIO_CLK       RCC_AHB1Periph_GPIOH //用户定义矩阵键盘COL3的时钟

#define  KEY_DOWN_LEVEL 0x00     //0x00表示按下为低电平
#define  KEY_UP_LEVEL   0xFF     //0xFF表示弹起为高电平

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/
typedef enum
{
  COL_3 = 0,    //第3列
  COL_2,        //第2列
  COL_1,        //第1列
  COL_0,        //第0列
  COL_MAX
}EnumHKey; 

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitKey4x4(void);     //初始化驱动
u8    ScanKey4x4(void);     //扫描Key4x4
u8    GetKey4x4(void);      //获取键值

#endif
