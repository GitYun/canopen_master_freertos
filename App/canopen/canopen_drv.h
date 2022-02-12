/**
  ******************************************************************************
  * @�ļ���     �� canopen_drv.h
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� CANOpen����ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _CANOPEN_DRV_H
#define _CANOPEN_DRV_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "bsp_can.h"


/* �궨�� --------------------------------------------------------------------*/
#define CANTX_QUEUE_LEN           10                       //CAN���г���(���е�����)(����)
#define CANTX_QUEUE_SIZE          19                       //CAN���д�С(һ�����г���) - sizeof(CanTxMsg)

#define CANRX_QUEUE_LEN           10                       //CAN���г���(���е�����)(����)
#define CANRX_QUEUE_SIZE          20                       //CAN���д�С(һ�����г���) - sizeof(CanRxMsg)

#define CANTX_STACK_SIZE          256                      //CANͨ�������ջ��С(����)
#define CANTX_TASK_PRIORITY       3                        //CANͨ���������ȼ�

#define CANRX_STACK_SIZE          256                      //CANͨ�������ջ��С(����)
#define CANRX_TASK_PRIORITY       3                        //CANͨ���������ȼ�


/* �������� ------------------------------------------------------------------*/
void CANOpen_Driver_Init(void);
void CANSend_Data(CanTxMsg TxMsg);
void CANRcv_DataFromISR(CanRxMsg *RxMsg);

void TIMx_DispatchFromISR(void);


#endif /* _CANOPEN_DRV_H */

/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
