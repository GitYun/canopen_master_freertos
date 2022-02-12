/**
  ******************************************************************************
  * @�ļ���     �� canfestival.h
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� CANOpen�ײ������ӿڶ���ͷ�ļ�
                   ��������Ҫʵ��canSend������λ��App\canopen\canopen_drv.c
                   �����ӿ��ڱ�����δʹ��(ͨ��bsp���������ƺ���ʵ����)
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _CANFESTIVAL_H
#define _CANFESTIVAL_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "applicfg.h"
#include "data.h"


/* �������� ------------------------------------------------------------------*/
void initTimer(void);
void clearTimer(void);

unsigned char canSend(CAN_PORT notused, Message *m);
unsigned char canInit(CO_Data * d, uint32_t bitrate);
void canClose(void);

void disable_it(void);
void enable_it(void);


#endif /* _CANFESTIVAL_H */

/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
