﻿/*********************************************************************************************************
* 模块名称: I2C.c
* 摘    要: 
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

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "I2C.h"
#include "SysTick.h"
#include <stm32f4xx_conf.h>

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
//读取SDA端口
#define READ_SDA()   	GPIO_ReadInputDataBit(USER_DEFINE_I2C_SDA_GPIO_PORT, USER_DEFINE_I2C_SDA_GPIO_PIN)  

//时钟线SCL输出高电平
#define SET_I2C_SCL()	GPIO_SetBits(USER_DEFINE_I2C_SCL_GPIO_PORT, USER_DEFINE_I2C_SCL_GPIO_PIN)   
//时钟线SCL输出低电平
#define CLR_I2C_SCL()	GPIO_ResetBits(USER_DEFINE_I2C_SCL_GPIO_PORT, USER_DEFINE_I2C_SCL_GPIO_PIN)  

//数据线SDA输出高电平
#define SET_I2C_SDA()	GPIO_SetBits(USER_DEFINE_I2C_SDA_GPIO_PORT, USER_DEFINE_I2C_SDA_GPIO_PIN)  
//数据线SDA输出低电平
#define CLR_I2C_SDA()	GPIO_ResetBits(USER_DEFINE_I2C_SDA_GPIO_PORT, USER_DEFINE_I2C_SDA_GPIO_PIN)  

#define ACK       1   //读取一个字节后，发送ACK
#define NACK      0   //读取一个字节后，发送NACK

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  void  ConfigI2CGPIO(void);    //配置I2C的GPIO
static  void  SetSDAAsInput(void);    //将SDA端设置为输入
static  void  SetSDAAsOutput(void);   //将SDA端设置为输出

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: ConfigI2CGPIO
* 函数功能: 配置I2C的GPIO 
* 输入参数: void 
* 输出参数: void 
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 
*********************************************************************************************************/
static  void  ConfigI2CGPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;    //定义结构体GPIO_InitStructure,用来配置I2C的GPIO

  RCC_AHB1PeriphClockCmd(USER_DEFINE_I2C_SCL_GPIO_CLK, ENABLE);       //使能I2C.SCL的时钟 

  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_I2C_SCL_GPIO_PIN;       //设置I2C.SCL的引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                  //设置I/O口速率为50MHz
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                      //推挽输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                      //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                       //设置引脚为上拉模式
  GPIO_Init(USER_DEFINE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);      //根据参数初始化I2C.SCL的GPIO端口
  
  GPIO_SetBits(USER_DEFINE_I2C_SCL_GPIO_PORT, USER_DEFINE_I2C_SCL_GPIO_PIN);    //I2C.SCL初始化为高电平
                                                                    
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_I2C_SDA_GPIO_PIN;       //设置I2C.SDA的引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                  //设置I/O口速率为50MHz
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                      //推挽输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                      //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                       //设置引脚为上拉模式
  GPIO_Init(USER_DEFINE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);      //根据参数初始化I2C.SDA的GPIO端口

  GPIO_SetBits(USER_DEFINE_I2C_SDA_GPIO_PORT, USER_DEFINE_I2C_SDA_GPIO_PIN);    //I2C.SDA初始化为高电平
} 

/*********************************************************************************************************
* 函数名称: SetSDAAsInput
* 函数功能: 将SDA端设置为输入 
* 输入参数: void 
* 输出参数: void  
* 返 回 值: void  
* 创建日期: 2018年03月01日
* 注    意: 
*********************************************************************************************************/
static  void  SetSDAAsInput(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;              //定义结构体GPIO_InitStructure，用来配置I2C.SDA
  
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_I2C_SDA_GPIO_PIN;   //设置I2C.SDA的引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //设置I/O口速率为50MHz
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;                   //输入模式
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   
  
  GPIO_Init(USER_DEFINE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);  //根据参数初始化I2C.SDA的GPIO端口
}

/*********************************************************************************************************
* 函数名称: SetSDAAsOutput
* 函数功能: 将SDA端设置为输出 
* 输入参数: void 
* 输出参数: void  
* 返 回 值: void  
* 创建日期: 2018年03月01日
* 注    意: 
*********************************************************************************************************/
static  void  SetSDAAsOutput(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;                //定义结构体GPIO_InitStructure,用来配置I2C.SDA
  
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_I2C_SDA_GPIO_PIN;   //设置I2C.SDA的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //设置I/O口速率为50MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;            
  
  GPIO_Init(USER_DEFINE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);  //根据参数初始化I2C.SDA的GPIO端口
}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitI2C
* 函数功能: 初始化IIC 
* 输入参数: void 
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
void InitI2C(void)
{
  ConfigI2CGPIO();        //配置I2C的GPIO
}

/*********************************************************************************************************
* 函数名称: GenI2CStartSig
* 函数功能: 产生IIC起始时序，准备发送或接收数据前必须由起始序列开始 
* 输入参数: void 
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: SCL为高电平时，SDA由高电平向低电平跳变，开始传输数据 
*           生成下图所示的波形图，即为起始时序 
*                1 2    3     4   
*                    __________     
*           SCL : __/          \_____ 
*                 ________          
*           SDA :         \___________ 
*********************************************************************************************************/
void GenI2CStartSig(void)
{
  SetSDAAsOutput();       //将数据线SDA设置为输出
  SET_I2C_SDA();          //1#数据线SDA输出高电平
  SET_I2C_SCL();          //2#时钟线SCL输出高电平，2-3之间的间隔须>4.7us   
  DelayNus(4);            //延时4us
  CLR_I2C_SDA();          //3#数据线SDA输出低电平，3-4之间的间隔须>4.0us 
  DelayNus(4);            //延时4us
  CLR_I2C_SCL();          //4#时钟线SCL输出低电平，保持I2C的时钟线SCL为低电平，准备发送或接收数据 
}

/*********************************************************************************************************
* 函数名称: GenI2CStopSig
* 函数功能: 产生IIC停止时序 
* 输入参数: void 
* 输出参数: void  
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: SCL为高电平时，SDA由低电平向高电平跳变，结束传输数据 
*          生成下图所示的波形图，即为停止时序 
*                1 2   3  4   
*                       _______________     
*          SCL : ______/          
*                __        ____________  
*          SDA:    \______/
*********************************************************************************************************/
void GenI2CStopSig(void)
{
  SetSDAAsOutput();       //将数据线SDA设置为输出
  CLR_I2C_SCL();          //1#时钟线SCL输出低电平
  CLR_I2C_SDA();          //2#数据线SDA输出低电平
  DelayNus(4);            //延时4us
  SET_I2C_SCL();          //3#时钟线SCL输出高电平，3-4之间的间隔须>4.7us 
  SET_I2C_SDA();          //4#数据线SDA输出高电平，发送I2C总线结束信号，4之后SDA须保持不小于4.0us的高电平
  DelayNus(4);            //延时4us
}

/*********************************************************************************************************
* 函数名称: I2CSendByte
* 函数功能: 发送一个字节，数据从高位开始发送出去 
* 输入参数: txd
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 下面是具体的时序图 
*                1 2     3      4
*                         ______
*           SCL: ________/      \______    
*                ______________________    
*           SDA: \\\___________________
*********************************************************************************************************/
void I2CSendByte(u8 txd)
{                        
  u8 t;                   //循环计数器
  
  SetSDAAsOutput();       //将数据线SDA设置为输出
  CLR_I2C_SCL();          //1#时钟线SCL输出低电平,开始数据传输
  
  for(t = 0; t < 8; t++)  //循环8次，从高到低取出字节的8个位
  {    
    if((txd&0x80) >> 7)   //2#取出字节最高位，并判断为‘0’还是‘1’，从而做出相应的操作
    {
      SET_I2C_SDA();      //数据线SDA输出高电平，数据位为‘1’
    }
    else
    {  
      CLR_I2C_SDA();      //数据线SDA输出低电平，数据位为‘0’
    }
    
    txd <<= 1;            //左移一位，次高位移到最高位
    
    DelayNus(2);          //延时2us
    SET_I2C_SCL();        //3#时钟线SCL输出高电平
    DelayNus(2);          //延时2us
    CLR_I2C_SCL();        //4#时钟线SCL输出低电平
    DelayNus(2);          //延时2us  
  }  
}

/*********************************************************************************************************
* 函数名称: I2CReadByte
* 函数功能: 读取一个字节，当ack=1时，发送ACK，当ack=0时，发送nACK 
* 输入参数: txd
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 下面是具体的时序图
*                       ______
*           SCL: ______/      \___        
*                ____________________    
*           SDA: \\\\______________\\\
*********************************************************************************************************/                   
u8 I2CReadByte(u8 ack)
{
  u8 i = 0;                 //i为循环计数器
  u8 receive = 0;           //receive用来存放接收的数据
  
  SetSDAAsInput();          //1#将数据线SDA设置为输入
  
  for(i = 0; i < 8; i++ )   //循环8次，从高到低读取字节的8个位
  {
    CLR_I2C_SCL();          //2#时钟线SCL输出低电平
    DelayNus(2);            //延时2us
    SET_I2C_SCL();          //3#时钟线SCL输出高电平
    
    receive <<= 1;          //左移一位，空出新的最低位
    
    if(READ_SDA())          //4#读取数据线SDA的数据位
    {
      receive++;            //在SCL的上升沿后，数据已经稳定，因此可以取该数据，存入最低位
    }
    
    DelayNus(1);            //延时1us
  } 
  
  if (NACK == ack)          //如果ack为NACK
  {   
    SendI2CNAck();          //发送NACK，无应答
  } 
  else                      //如果ack为ACK
  {
    SendI2CAck();           //发送ACK，应答   
  }
  
  return receive;           //返回读取到的数据
}

/*********************************************************************************************************
* 函数名称: I2CWaitACK
* 函数功能: 等待应答信号到来 
* 输入参数: void
* 输出参数: void
* 返 回 值: 1，接收应答失败；0，接收应答成功
* 创建日期: 2018年03月01日
* 注    意: 当SDA拉低后，表示接收到ACK信号，然后，拉低SCL，根据实际情况做出是否继续传递信号的判断
*           此处表示发送端收到接收端的ACK
*                _______|____     
*           SCL:        |    \_________    
*                _______|     
*           SDA:         \_____________    
*********************************************************************************************************/
u8 I2CWaitAck(void)
{
  u8 ucErrTime = 0;
  
  SetSDAAsInput();        //将数据线SDA设置为输出
  SET_I2C_SDA();          //将数据线SDA设置为输入
  DelayNus(1);            //延时1us
  SET_I2C_SCL();          //时钟线SCL输出高电平
  DelayNus(1);            //延时1us
  
  while(READ_SDA())       //读回来的数据如果是高电平，即接收端没有应答
  {
    ucErrTime++;          //计数器加1
    
    if(ucErrTime > 250)   //如果超过250次，则判断为接收端出现故障，因此发送结束信号
    {
      GenI2CStopSig();    //产生一个停止信号
      
      return 1;           //返回值为1，表示没有收到应答信号
    }
  }
  
  CLR_I2C_SCL();          //表示已收到应答信号，时钟线SCL输出低电平，钳住I2C总线
  
  return 0;               //返回值为0，表示接收应答成功  
}

/*********************************************************************************************************
* 函数名称: SendI2CAck
* 函数功能: 发送应答信号 
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 下面是具体的时序图 
*                 1 2     3      4
*                         ______
*           SCL: ________/      \______    
*                __     
*           SDA:   \___________________    
*********************************************************************************************************/
void SendI2CAck(void)
{
  CLR_I2C_SCL();          //1#时钟线SCL输出低电平，开始传送应答信号
  SetSDAAsOutput();       //将数据线SDA设置为输出
  CLR_I2C_SDA();          //2#数据线SDA输出低电平
  DelayNus(2);            //延时2us
  SET_I2C_SCL();          //3#时钟线SCL输出高电平,在SCL上升沿前就要把SDA拉低，为应答信号
  DelayNus(2);            //延时2us
  CLR_I2C_SCL();          //4#时钟线SCL输出低电平，钳住I2C总线
}

/*********************************************************************************************************
* 函数名称: SendI2CNAck
* 函数功能: 不发送应答信号 
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 下面是具体的时序图 
*               1 2     3      4
*                        ______
*          SCL: ________/      \______    
*               __ ___________________    
*          SDA: __/
*********************************************************************************************************/
void SendI2CNAck(void)
{
  CLR_I2C_SCL();          //1#拉低时钟线，开始传送非应答信号
  SetSDAAsOutput();       //将数据线SDA设置为输出
  SET_I2C_SDA();          //2#数据线SDA输出高电平
  DelayNus(2);            //延时2us
  SET_I2C_SCL();          //3#时钟线SCL输出高电平，在SCL上升沿前就要把SDA拉高，为非应答信号
  DelayNus(2);            //延时2us
  CLR_I2C_SCL();          //4#时钟线SCL输出低电平，钳住I2C总线
}
