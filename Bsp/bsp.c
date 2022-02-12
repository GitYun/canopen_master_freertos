/**
  ******************************************************************************
  * @文件名     ： bsp.c
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2018年11月14日
  * @摘要       ： 底层驱动源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2018-11-14 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "bsp.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "bsp_usart.h"
#include "retarget.h"

/************************************************
函数名称 ： LED_Initializes
功    能 ： LED初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void LED_Initializes(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* 使能时钟 */
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  /* 引脚配置 */
  GPIO_InitStructure.GPIO_Pin   = LED_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

  LED_OFF();
}

/************************************************
函数名称 ： BSP_Init
功    能 ： 底层驱动初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void BSP_Init(void)
{
  LED_Initializes();                             //LED底层初始化

  CAN_Initializes();                             //CAN底层初始化
  TIM_Initializes();                             //TIM底层初始化
  USART_Initializes();                           //USART底层初始化
}


/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
