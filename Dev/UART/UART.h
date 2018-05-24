/*********************************************************************************************************
* 模块名称: UART.h
* 摘    要: 串口模块，包括串口模块初始化，以及中断服务函数处理，以及读写串口函数实现
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
#ifndef _UART_H_
#define _UART_H_

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include <stdio.h>
#include "DataType.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define UART_BUF_SIZE 100           //设置缓冲区的大小

#define USER_DEFINE_USART                        USART1                        //用户定义USART的端口  
#define USER_DEFINE_USART_CLK                    RCC_APB2Periph_USART1         //用户定义USART的时钟 
#define USER_DEFINE_USART_BAUDRATE               115200                        //用户定义USART的波特率
#define USER_DEFINE_USART_WORDLENGTH             USART_WordLength_8b           //用户定义USART传输的字长
#define USER_DEFINE_USART_STOPBITS               USART_StopBits_1              //用户定义USART的停止位
#define USER_DEFINE_USART_PARITY                 USART_Parity_No               //用户定义USART的奇偶校验位
#define USER_DEFINE_USART_MODE                   USART_Mode_Rx | USART_Mode_Tx //用户定义USART的模式
#define USER_DEFINE_USART_HRDWAREFLOWCONTROL     USART_HardwareFlowControl_None//用户定义USART的硬件流控制
  
#define USER_DEFINE_USART_TX_GPIO_PORT           GPIOA                   //用户定义USART.TX的GPIO端口
#define USER_DEFINE_USART_TX_GPIO_PIN            GPIO_Pin_9              //用户定义USART.TX的引脚
#define USER_DEFINE_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOA    //用户定义USART.TX的时钟
#define USER_DEFINE_USART_TX_AF                  GPIO_AF_USART1
#define USER_DEFINE_USART_TX_SOURCE              GPIO_PinSource9

#define USER_DEFINE_USART_RX_GPIO_PORT           GPIOA                   //用户定义USART.RX的GPIO端口 
#define USER_DEFINE_USART_RX_GPIO_PIN            GPIO_Pin_10             //用户定义USART.RX的引脚
#define USER_DEFINE_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOA    //用户定义USART.RX的时钟
#define USER_DEFINE_USART_RX_AF                  GPIO_AF_USART1
#define USER_DEFINE_USART_RX_SOURCE              GPIO_PinSource10
  
#define USER_DEFINE_USART_IRQHandler             USART1_IRQHandler       //用户定义串口的中断服务函数
#define USER_DEFINE_USART_IRQ                    USART1_IRQn             //用户定义串口的中断通道

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              API函数声明
*********************************************************************************************************/
void  InitUART(void);               //初始化UART模块
u8    WriteUART(u8 *pBuf, u8 len);  //写串口，返回已写入的字节数
u8    ReadUART(u8 *pBuf, u8 len);   //读串口，返回读到的字节数

#endif
