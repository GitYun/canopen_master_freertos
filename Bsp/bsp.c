/**
  ******************************************************************************
  * @�ļ���     �� bsp.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� �ײ�����Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-11-14 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "bsp_usart.h"
#include "retarget.h"

/************************************************
�������� �� LED_Initializes
��    �� �� LED��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void LED_Initializes(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* ʹ��ʱ�� */
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);

  /* �������� */
  GPIO_InitStructure.GPIO_Pin   = LED_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

  LED_OFF();
}

/************************************************
�������� �� BSP_Init
��    �� �� �ײ�������ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void BSP_Init(void)
{
  LED_Initializes();                             //LED�ײ��ʼ��

  CAN_Initializes();                             //CAN�ײ��ʼ��
  TIM_Initializes();                             //TIM�ײ��ʼ��
  USART_Initializes();                           //USART�ײ��ʼ��
}


/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
