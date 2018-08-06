/*********************************************************************************************************
* 模块名称: Key3x3.c
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

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "Key3x3.h"
#include <stm32f10x_conf.h>
#include "UART.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
//读取COL3-PC1 引脚的电平
#define COL3  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)
//读取COL2-PC2 引脚的电平
#define COL2  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)
//读取COL1-PC0 引脚的电平
#define COL1  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)

//读取ROW3-PA8 引脚的电平
#define ROW3  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
//读取ROW2-PC9 引脚的电平
#define ROW2  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)
//读取ROW1-PC8 引脚的电平
#define ROW1  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8)

#define  KEY_DOWN_LEVEL 0x00     //0x00表示按下为低电平
#define  KEY_UP_LEVEL   0xFF     //0xFF表示弹起为高电平

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/
typedef enum
{
  COL_1 = 0,    //第3列
  COL_2,        //第2列
  COL_3,        //第1列
  COL_MAX
}EnumHKey; 

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/
static u8 s_iColRow = 0xFF;

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static void ConfigKey3x3GPIO(void);
static void WrRow(u8 vol);
static u8   RdCol(void);
static u8   RdRow(void);

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: ConfigKey3x3GPIO
* 函数功能: 配置KEY4X4的GPIO 
* 输入参数: void 
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年01月01日
* 注    意:         |           |           |       
*           ROW3-----|-----------|-----------|------
*           ROW2-----|-----------|-----------|------
*           ROW1-----|-----------|-----------|------
*                  COL3       COL2         COL1     
*            0  1  2  3   
*            4  5  6  7   
*            8  9  A  B   
*            C  D  E  F 
*            ROW3-PA8 
*            ROW2-PC9 
*            ROW1-PC8  
*            COL3-PC1 
*            COL2-PC2 
*            COL1-PC0
*********************************************************************************************************/
static void ConfigKey3x3GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStrucrute;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  
  GPIO_InitStrucrute.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStrucrute.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStrucrute.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStrucrute);
  
  GPIO_InitStrucrute.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStrucrute.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStrucrute.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStrucrute);
  
  GPIO_InitStrucrute.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStrucrute.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStrucrute.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStrucrute);
  
  GPIO_InitStrucrute.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStrucrute.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStrucrute.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStrucrute);
  
  GPIO_InitStrucrute.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStrucrute.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStrucrute.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStrucrute);
  
  GPIO_InitStrucrute.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStrucrute.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStrucrute.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStrucrute);  
}

/*********************************************************************************************************
* 函数名称: RdRow
* 函数功能: 读ROW
* 输入参数: void
* 输出参数: void
* 返 回 值: ROW的电平值（ROW0/ROW1/ROW2/ROW3）
* 创建日期: 2018年01月01日
* 注    意: ROW3-PA8
*           ROW2-PC9
*           ROW1-PC8
*********************************************************************************************************/
static void WrRow(u8 row)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_8, (BitAction)((row >> 2) & 0x01));     //在ROW3-PA8写入相应的值
  GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)((row >> 1) & 0x01));     //在ROW2-PC9写入相应的值
  GPIO_WriteBit(GPIOC, GPIO_Pin_8, (BitAction)((row >> 0) & 0x01));     //在ROW1-PC8写入相应的值
}

/*********************************************************************************************************
* 函数名称: RdRow
* 函数功能: 读ROW
* 输入参数: void
* 输出参数: void
* 返 回 值: ROW的电平值（ROW0/ROW1/ROW2/ROW3）
* 创建日期: 2018年01月01日
* 注    意: COL3-PC1
*           COL2-PC2
*           COL1-PC0
*********************************************************************************************************/
static u8 RdCol(void)
{
  return (u8)( 1 << 3    |
            (COL3 << 2)  |    //读取COL3-PC2引脚的电平
            (COL2 << 1)  |    //读取COL2-PC1引脚的电平
            (COL1 << 0)    ); //读取COL1-PC0引脚的电平
}

/*********************************************************************************************************
* 函数名称: RdRow
* 函数功能: 读ROW
* 输入参数: void
* 输出参数: void
* 返 回 值: ROW的电平值（ROW0/ROW1/ROW2/ROW3）
* 创建日期: 2018年01月01日
* 注    意: ROW3-PA8
*           ROW2-PC9
*           ROW1-PC8
*********************************************************************************************************/
static u8 RdRow(void)
{
  return (u8)( 1 << 3    |
            (ROW3 << 2)  |     //读取ROW3-PA8引脚的电平
            (ROW2 << 1)  |     //读取ROW2-PC9引脚的电平
            (ROW1 << 0)    );  //读取ROW1-PC8引脚的电平
}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitKey3x3
* 函数功能: 初始化Key4x4
* 输入参数: void 
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年01月01日
* 注    意: 
*********************************************************************************************************/
void  InitKey3x3(void)
{
  ConfigKey3x3GPIO();
}

/*********************************************************************************************************
* 函数名称: ScanKey3x3
* 函数功能: 按键扫描，2ms扫描一次
* 输入参数: void 
* 输出参数: void
* 返 回 值: s_iColRow
* 创建日期: 2018年01月01日
* 注    意: 
*********************************************************************************************************/
u8 ScanKey3x3(void)
{
  static i16 s_iCnt10 = 0;
  static u8 s_iRowVal = 0x0E;
  static u8 s_iColVal[COL_MAX];
  static u8 s_iColKeyDownFlag[COL_MAX];
  
  static u8 s_arrColKeyDownLevel[COL_MAX] = {0x0E, 0x0D, 0x0B};
  static i32 s_arrColCnt[3] = {0, 0, 0};
  i16 i;
  
  //每隔20ms进行一次行扫描输出，低四位循环移位
  if(s_iCnt10 >= 9)
  {
    s_iRowVal = ((s_iRowVal & 0x07) << 1) | ((s_iRowVal & 0x04) >> 2) | 0x08;
    WrRow(s_iRowVal & 0x0F);
    s_iCnt10 = 0;
  }
  else
  {
    s_iCnt10++;
  }
  
  for(i = 0; i < 3; i++)
  {
    if(RdCol() == s_arrColKeyDownLevel[i])
    {
      s_arrColCnt[i] = 0;
    }
    else
    {
      s_arrColCnt[i]++;
    }
    
    if(RdCol() == s_arrColKeyDownLevel[i] || s_arrColCnt[i] % 4 == 0)
    {
      s_iColVal[i] = s_iColVal[i] << 1;
      
      switch(i)
      {
        case COL_3:
          s_iColVal[i] = s_iColVal[i] | COL3;
          break;
        case COL_2:
          s_iColVal[i] = s_iColVal[i] | COL2;
          break;
        case COL_1:
          s_iColVal[i] = s_iColVal[i] | COL1;
          break;
        default:
          break;
      }
    }
    
    if(s_iColVal[i] == KEY_DOWN_LEVEL && s_iColKeyDownFlag[i] == FALSE)
    {
      s_iColRow = RdCol() << 4 | RdRow();
      s_iColKeyDownFlag[i] = TRUE;
    }
    else if(s_iColVal[i] == KEY_UP_LEVEL && s_iColKeyDownFlag[i] == TRUE)
    {
      s_iColKeyDownFlag[i] = FALSE;
    }
  }
  
  return s_iColRow;
}

/*********************************************************************************************************
* 函数名称: GetKey3x3
* 函数功能: 通过列-行按键值获取键值
* 输入参数: void 
* 输出参数: void
* 返 回 值: 键值，最左上角为0，最右下角为8
* 创建日期: 2018年01月01日
* 注    意: 
*********************************************************************************************************/
u8 GetKey3x3(void)
{
  u8 KeyVal = 0;
  
  switch(s_iColRow)
  {
    case 0xBB:      //键值为1
      KeyVal = 1;  
      break;
    case 0xDB:      //键值为2
      KeyVal = 2;
      break;
    case 0xEB:      //键值为3
      KeyVal = 3;
      break;
    case 0xBD:      //键值为4
      KeyVal = 4;
      break;
    case 0xDD:      //键值为5
      KeyVal = 5;
      break;
    case 0xED:      //键值为6
      KeyVal = 6;
      break;
    case 0xBE:      //键值为7
      KeyVal = 7;
      break;
    case 0xDE:      //键值为8
      KeyVal = 8;
      break;
    case 0xEE:      //键值为9
      KeyVal = 9;
      break;
    default:
      KeyVal =255;
      break;
  }
  
  s_iColRow = 0xFF;
  
  return KeyVal;
}
