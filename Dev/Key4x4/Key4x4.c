/*********************************************************************************************************
* 模块名称: Key4x4.c
* 摘    要: 
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

/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include <stm32f4xx_conf.h>
#include "Key4x4.h"
#include "UART.h"

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
//读取COL3-PH7 引脚的电平
#define COL3	GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_COL3_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_COL3_GPIO_PIN)    
//读取COL2-PH9 引脚的电平
#define COL2	GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_COL2_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_COL2_GPIO_PIN)    
//读取COL1-PH10引脚的电平
#define COL1	GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_COL1_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_COL1_GPIO_PIN)   
//读取COL0-PH11引脚的电平
#define COL0	GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_COL0_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_COL0_GPIO_PIN)   

//读取ROW3-PG7 引脚的电平
#define ROW3  GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PIN)    
//读取ROW2-PG6 引脚的电平
#define ROW2  GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PIN)    
//读取ROW1-PG3 引脚的电平
#define ROW1  GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PIN)    
//读取ROW0-PH6 引脚的电平
#define ROW0  GPIO_ReadInputDataBit(USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PORT, \
                                          USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PIN)    

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/
static  u8  s_iColRow = 0xFF;           //读取HEey和LKey

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  void  ConfigKey4x4GPIO(void);   //配置KEY4X4的GPIO
static  void  WrRow(u8 vol);            //写ROW，ROW电平值（ROW0/ROW1/ROW2/ROW3）
static  u8    RdCol(void);              //读COL，COL电平值（COL3/COL2/COL1/COL0）
static  u8    RdRow(void);              //读ROW，ROW电平值（ROW0/ROW1/ROW2/ROW3）

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: ConfigKey4x4GPIO
* 函数功能: 配置KEY4X4的GPIO 
* 输入参数: void 
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年01月01日
* 注    意:         |           |           |           |
*          ROW3-----|-----------|-----------|-----------|--------
*          ROW2-----|-----------|-----------|-----------|--------
*          ROW1-----|-----------|-----------|-----------|--------
*          ROW0-----|-----------|-----------|-----------|--------
*                  COL3       COL2         COL1        COL0
*           0  1  2  3  
*           4  5  6  7  
*           8  9  A  B  
*           C  D  E  F
*           ROW3-PH6
*           ROW2-PG3
*           ROW1-PG6
*           ROW0-PG7
*           COL3-PH7
*           COL2-PH9
*           COL1-PH10
*           COL0-PH11
*********************************************************************************************************/
static  void  ConfigKey4x4GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;         //定义结构体GPIO_InitStructure,用来配置矩阵键盘的GPIO

  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_ROW0_GPIO_CLK, ENABLE);//使能矩阵键盘的ROW0引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PIN; //设置矩阵键盘ROW0的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                        //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;                       //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘ROW0的GPIO端口	        

  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_ROW1_GPIO_CLK, ENABLE);//使能矩阵键盘的ROW1引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PIN; //设置矩阵键盘ROW1的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                        //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;                       //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘ROW1的GPIO端口

  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_ROW2_GPIO_CLK, ENABLE);//使能矩阵键盘的ROW2引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PIN; //设置矩阵键盘ROW2的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                        //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;                       //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘ROW2的GPIO端口

  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_ROW3_GPIO_CLK, ENABLE);//使能矩阵键盘的ROW3引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PIN; //设置矩阵键盘ROW3的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                        //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;                       //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘ROW3的GPIO端口
  
  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_COL0_GPIO_CLK, ENABLE);//使能矩阵键盘的COL0引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_COL0_GPIO_PIN; //设置矩阵键盘COL0的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;                         //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                         //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_COL0_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘COL0的GPIO端口
  
  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_COL1_GPIO_CLK, ENABLE);//使能矩阵键盘的COL1引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_COL1_GPIO_PIN; //设置矩阵键盘COL1的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;                         //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                         //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_COL1_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘COL1的GPIO端口
  
  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_COL2_GPIO_CLK, ENABLE);//使能矩阵键盘的COL2引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_COL2_GPIO_PIN; //设置矩阵键盘COL2的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;                         //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                         //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_COL2_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘COL2的GPIO端口
  
  RCC_AHB1PeriphClockCmd (USER_DEFINE_KEY_MATRIX_COL3_GPIO_CLK, ENABLE);//使能矩阵键盘的COL3引脚时钟
  GPIO_InitStructure.GPIO_Pin   = USER_DEFINE_KEY_MATRIX_COL3_GPIO_PIN; //设置矩阵键盘COL3的引脚
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;                         //设置工作模式为输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                      //设置I/O速率为2MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                        //设置引脚的输出类型为推挽输出
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                         //设置引脚为下拉模式 
  GPIO_Init(USER_DEFINE_KEY_MATRIX_COL3_GPIO_PORT, &GPIO_InitStructure);//根据参数初始化矩阵键盘COL3的GPIO端口
}

/*********************************************************************************************************
* 函数名称: WrRow
* 函数功能: 写ROW
* 输入参数: row，即ROW电平值（ROW0/ROW1/ROW2/ROW3）
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年01月01日
* 注    意: ROW3-PH6
*           ROW2-PG3
*           ROW1-PG6
*           ROW0-PG7
*********************************************************************************************************/
static  void  WrRow(u8 row)
{
  GPIO_WriteBit(USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PORT, USER_DEFINE_KEY_MATRIX_ROW3_GPIO_PIN, 
                                            (BitAction)((row >> 0) & 0x01));   //在ROW3-PH6写入相应的值
  GPIO_WriteBit(USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PORT, USER_DEFINE_KEY_MATRIX_ROW2_GPIO_PIN, 
                                            (BitAction)((row >> 1) & 0x01));   //在ROW2-PG3写入相应的值
  GPIO_WriteBit(USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PORT, USER_DEFINE_KEY_MATRIX_ROW1_GPIO_PIN, 
                                            (BitAction)((row >> 2) & 0x01));   //在ROW1-PG6写入相应的值
  GPIO_WriteBit(USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PORT, USER_DEFINE_KEY_MATRIX_ROW0_GPIO_PIN, 
                                            (BitAction)((row >> 3) & 0x01));   //在ROW0-PG7写入相应的值
}

/*********************************************************************************************************
* 函数名称: RdCol
* 函数功能: 读COL
* 输入参数: void
* 输出参数: void
* 返 回 值: COL的电平值（COL3/COL2/COL1/COL0）
* 创建日期: 2018年01月01日
* 注    意: COL3(COL3)-PH7
*           COL2(COL2)-PH9
*           COL1(COL1)-PH10
*           COL0(COL0)-PH11
*********************************************************************************************************/
static  u8  RdCol(void)
{
 return(  (COL3 << 3)  |       //读取COL3-PH7引脚的电平
          (COL2 << 2)  |       //读取COL2-PH9引脚的电平
          (COL1 << 1)  |       //读取COL1-PH10引脚的电平
          (COL0 << 0)  );      //读取COL0-PH11引脚的电平
}

/*********************************************************************************************************
* 函数名称: RdRow
* 函数功能: 读ROW
* 输入参数: void
* 输出参数: void
* 返 回 值: ROW的电平值（ROW0/ROW1/ROW2/ROW3）
* 创建日期: 2018年01月01日
* 注    意: ROW3-PH6
*           ROW2-PG3
*           ROW1-PG6
*           ROW0-PG7
*********************************************************************************************************/
static  u8  RdRow(void)
{
  return( (ROW3 << 3) |      //读取ROW3-PG7引脚的电平
          (ROW2 << 2) |      //读取ROW2-PG6引脚的电平
          (ROW1 << 1) |      //读取ROW1-PG3引脚的电平
          (ROW0 << 0) );     //读取ROW0-PH6引脚的电平
}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitKey4x4
* 函数功能: 初始化Key4x4
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2018年01月01日
* 注    意:
*********************************************************************************************************/
void InitKey4x4(void)
{ 
  ConfigKey4x4GPIO();   //配置KEY4X4的GPIO 
}

/*********************************************************************************************************
* 函数名称: ScanKey4x4
* 函数功能: 按键扫描，2ms扫描一次
* 输入参数: void
* 输出参数: void
* 返 回 值: s_iColRow
* 创建日期: 2018年01月01日
* 注    意: 
*********************************************************************************************************/
u8  ScanKey4x4(void)
{
  static  i16 s_iCnt10   = 0;             //10计数器，0-9，计数到9表示20毫秒，用以进行行扫描输出
  static  u8  s_iRowVal = 0x0E;           //行输出值，1110，依次为ROW0/ROW1/ROW2/ROW3
  static  u8  s_iColVal[COL_MAX];         //列输入值，每隔2毫秒从左端移入
  static  u8  s_iColKeyDownFlag[COL_MAX]; //列键按下标志，TRUE-按键按下，FALSE-按键弹起                                             
  //HEKY的电平值（COL3/COL2/COL1/COL0），即[0]-COL3，[3]-COL1
  static  u8  s_arrColKeyDownLevel[COL_MAX] = {0x07, 0x0B, 0x0D, 0x0E};
  static  i32 s_arrColCnt[COL_MAX] = {0, 0, 0, 0};  
  i16 i;                                  //循环计数器
 
  //每隔20ms进行一次行扫描输出，低四位循环移位
  if(s_iCnt10 >= 9)
  {
    s_iRowVal = ((s_iRowVal & 0x07) << 1) | ((s_iRowVal & 0x08) >> 3);  //低四位循环移位 
    WrRow(s_iRowVal & 0x0F);              //每隔20ms调用一次，进行一次行扫描输出 
    s_iCnt10 = 0;                         //计时器置0
  }
  else
  {
    s_iCnt10++;                           //计时器递增
  }   
  
  for(i = 0; i < 4; i++)
  {
    if(RdCol() == s_arrColKeyDownLevel[i])
    {
      s_arrColCnt[i] = 0;                 //以按键按下为时间基准，进行计数
    }
    else
    {
      s_arrColCnt[i]++;
    }
    
    //以按键按下为时间基准，每隔4个计数进行一次列按键值读取，如进行COL3读取时，以检测到COL3按下时为基准
    //每隔4个计数，即每隔8毫秒读取COL3，这样就可以将断裂的COL3时序连在一起，与独立按键类似
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
        case COL_0:
          s_iColVal[i] = s_iColVal[i] | COL0;
          break;
        default:
          break;
      }
    }
  
    //采样8个低电平时，表示有列按键按下
    if(s_iColVal[i] == KEY_DOWN_LEVEL && s_iColKeyDownFlag[i] == FALSE)
    {
      s_iColRow = RdCol() << 4 | RdRow();
      s_iColKeyDownFlag[i] = TRUE;            //表示按键处于按下状态
    }
    //采样8个高电平时，表示列按键弹起
    else if(s_iColVal[i] == KEY_UP_LEVEL && s_iColKeyDownFlag[i] == TRUE)
    {
      s_iColKeyDownFlag[i] = FALSE;           //表示按键处于弹起状态
    }
  }

  return(s_iColRow);      //返回列-行按键值     
}

/*********************************************************************************************************
* 函数名称: GetKey4x4
* 函数功能: 通过列-行按键值获取键值
* 输入参数: void
* 输出参数: void
* 返 回 值: 键值，最左上角为0，最右下角为F
* 创建日期: 2018年01月01日
* 注    意: 
*********************************************************************************************************/
u8  GetKey4x4(void)
{
  u8 keyVal = 0;          //用来存放键值

  switch(s_iColRow)
  {
    case 0x7E:
      keyVal = 0;     //键值为0
      break;
    case 0xBE:
      keyVal = 1;     //键值为1
      break;      
    case 0xDE:
      keyVal = 2;     //键值为2
      break;
    case 0xEE:
      keyVal = 3;     //键值为3
      break;
    case 0x7D:
      keyVal = 4;     //键值为4
      break;
    case 0xBD:
      keyVal = 5;     //键值为5
      break;      
    case 0xDD:
      keyVal = 6;     //键值为6
      break;
    case 0xED:
      keyVal = 7;     //键值为7
      break;         
    case 0x7B:
      keyVal = 8;     //键值为8
      break;
    case 0xBB:
      keyVal = 9;     //键值为9
      break;      
    case 0xDB:
      keyVal = 10;    //键值为10
      break;
    case 0xEB:
      keyVal = 11;    //键值为11
      break;      
    case 0x77:
      keyVal = 12;    //键值为12
      break;
    case 0xB7:
      keyVal = 13;    //键值为13
      break;      
    case 0xD7 :
      keyVal = 14;    //键值为14
      break;
    case 0xE7:
      keyVal = 15;    //键值为15
      break;
    default:
      keyVal = 255;
      break;
  }
  
  s_iColRow = 0xFF;   //0xFF表示没有按键按下

  return(keyVal);     //返回按键的值
}
