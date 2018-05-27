 /*********************************************************************************************************
* 模块名称: ADC.c
* 摘    要: 
* 当前版本: 1.0.0
* 作    者: SZLY(COPYRIGHT 2018 SZLY. All rights reserved.)
* 完成日期: 2018年04月19日
* 内    容:
* 注    意: none                                                                  
**********************************************************************************************************
* 取代版本: 1.0.0
* 作    者:
* 完成日期: 
* 修改内容: 
* 修改文件: 
*********************************************************************************************************/
/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "ADC.h"
#include "SysTick.h"
#include "UART.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/ 
static u16 ADC_ConvertedValue;   //存放ADC转换值

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
void ADCNVICConfig(void);     //配置中断优先级
//static u16 GetADC(void);    //获得ADC采样值

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: GetADC
* 函数功能: 获得ADC采样值
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
//static u16 GetADC(void)   
//{ 
//  // 配置 ADC 通道转换顺序为1，第一个转换，采样时间为3个时钟周期
//  ADC_RegularChannelConfig(USER_DEFINE_ADC, USER_DEFINE_ADC_CHANNEL, 1, ADC_SampleTime_56Cycles);              

//  ADC_SoftwareStartConv(USER_DEFINE_ADC);//开始adc转换，软件触发
//  
//  while(!ADC_GetFlagStatus(USER_DEFINE_ADC, ADC_FLAG_EOC));  //等待转换结束

//  return ADC_GetConversionValue(USER_DEFINE_ADC);             //返回最近一次ADC规则组的转换结果
//}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitADC
* 函数功能: 初始化ADC
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意: 这里我们仅以规则通道为例
*********************************************************************************************************/  
void InitADC(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;           //定义结构体GPIO_InitStructure，用来配置ADC通道的GPIO
  ADC_InitTypeDef ADC_InitStructure;             //定义结构体ADC_InitStructure,用来配置ADC
  ADC_CommonInitTypeDef ADC_CommonInitStructure; //定义结构体ADC_CommonInitStructure，用来配置ADC通用寄存器    
  
  RCC_AHB1PeriphClockCmd(USER_DEFINE_ADC_GPIO_CLK, ENABLE);                     //使能 GPIO 时钟
                      
  GPIO_InitStructure.GPIO_Pin = USER_DEFINE_ADC_GPIO_PIN;                       //配置 IO
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                                 //模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;                             //不上拉不下拉
  GPIO_Init(USER_DEFINE_ADC_GPIO_PORT, &GPIO_InitStructure);                    //初始化ADC的GPIO端口  
                      
  RCC_APB2PeriphClockCmd(USER_DEFINE_ADC_CLK , ENABLE);                         //开启ADC时钟
                    
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                      //独立ADC模式
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                   //时钟为fpclk 4分频  
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;       //禁止DMA直接访问模式 
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles; //采样时间间隔  
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;              //ADC 分辨率  
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //禁止扫描模式，多通道采集才需要   
//  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;      //单次转换
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                  //连续转换，转换完成自动进行下次转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止外部边沿触发  
  //ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;//外部触发通道，软件触发不用配置
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //数据右对齐 
  ADC_InitStructure.ADC_NbrOfConversion = 1;                          //转换通道 1个                              
  ADC_Init(USER_DEFINE_ADC, &ADC_InitStructure);                      //根据ADC_InitStruct中指定的参数初始化ADC

  // 配置 ADC 通道转换顺序为1，第一个转换，采样时间为56个时钟周期
  ADC_RegularChannelConfig(USER_DEFINE_ADC, USER_DEFINE_ADC_CHANNEL, 1, ADC_SampleTime_56Cycles);
  
  ADC_ITConfig(USER_DEFINE_ADC, ADC_IT_EOC, ENABLE);  //ADC转换结束产生中断，在中断服务程序中读取转换值
  ADC_Cmd(USER_DEFINE_ADC, ENABLE);                   //使能ADC
  ADC_SoftwareStartConv(USER_DEFINE_ADC);             //开始adc转换，软件触发
  
  ADCNVICConfig();     //配置ADC中断优先级
}

/*********************************************************************************************************
* 函数名称: ADCNVICConfig
* 函数功能: 配置中断优先级
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
void ADCNVICConfig(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;        //定义结构体NVIC_InitStructure，用来配置ADC的NVIC
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);             //中断优先组
  
  NVIC_InitStructure.NVIC_IRQChannel = USER_DEFINE_ADC_IRQ;   //配置中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //子优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能中断通道
  
  NVIC_Init(&NVIC_InitStructure);                             //根据参数初始化中断NVIC
}

/*********************************************************************************************************
* 函数名称: GetADCAverage
* 函数功能: 计算ADC采样数据的平均值
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
u16 GetADCAverage(u8 sampletimes)
{
  float tempVal = 0;                                //定义一个变量用来表示采样数据之和
  u8 t;                                             //定义一个变量执行循环语句
  
  for(t = 0; t < sampletimes; t++)                  //循环采样加和
  {
    //tempVal += GetADC();                          //对采样数据进行加和并赋给tempVal
                      
    tempVal += ADC_ConvertedValue;                  //累加转换值
    
    DelayNms(5);                                    //延时5ms
  }
  
  return tempVal / sampletimes;                     //返回采样数据的平均值
}    

/*********************************************************************************************************
* 函数名称: ADC_IRQHandler
* 函数功能: ADC 转换完成中断服务程序
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年03月01日
* 注    意:
*********************************************************************************************************/
void ADC_IRQHandler(void)
{
	if(ADC_GetITStatus(USER_DEFINE_ADC, ADC_IT_EOC) == SET)         //转换完成
	{
  
    ADC_ConvertedValue = ADC_GetConversionValue(USER_DEFINE_ADC); //读取ADC的转换值
	}
  
	ADC_ClearITPendingBit(USER_DEFINE_ADC, ADC_IT_EOC);             //清除转换完成标志
}	
