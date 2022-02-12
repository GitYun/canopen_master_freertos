/**
  ******************************************************************************
  * @�ļ���     �� bsp.h
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� �ײ�����ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"


/* �궨�� --------------------------------------------------------------------*/
#define LED_GPIO_CLK              RCC_APB2Periph_GPIOA
#define LED_PIN                   GPIO_Pin_8
#define LED_GPIO_PORT             GPIOA

/* LED���� */
#define LED_ON()                  GPIO_SetBits(LED_GPIO_PORT, LED_PIN)
#define LED_OFF()                 GPIO_ResetBits(LED_GPIO_PORT, LED_PIN)
#define LED_TOGGLE()              (LED_GPIO_PORT->ODR ^= LED_PIN)


/* �������� ------------------------------------------------------------------*/
void BSP_Init(void);


#endif /* _BSP_H */

/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
