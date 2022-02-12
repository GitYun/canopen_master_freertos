/**
  ******************************************************************************
  * @�ļ���     �� canopen_drv.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� CANOpen����Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-11-14 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "canopen_drv.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "bsp_usart.h"
#include "TestMaster.h"


/* ��̬���� ------------------------------------------------------------------*/
static xQueueHandle xCANSendQueue = NULL;        //CAN���Ͷ���
static xQueueHandle xCANRcvQueue = NULL;         //CAN���ն���

/* ��ʱ��TIM��ر��� */
static TIMEVAL last_counter_val = 0;
static TIMEVAL elapsed_time = 0;


/* ��̬���� ------------------------------------------------------------------*/
static void CANSend_Task(void *pvParameters);
static void CANRcv_Task(void *pvParameters);


/************************************************
�������� �� CANOpen_Driver_Init
��    �� �� CANOpen������ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void CANOpen_Driver_Init(void)
{
  BaseType_t xReturn;

  /* �������� */
  if(xCANSendQueue == NULL)
  {
    xCANSendQueue = xQueueCreate(CANTX_QUEUE_LEN, sizeof(CanTxMsg));
    if(xCANSendQueue == NULL)
    {
      printf("CANSendQueue create failed");
      return;                                    //�������Ͷ���ʧ��
    }
  }

  if(xCANRcvQueue == NULL)
  {
    xCANRcvQueue = xQueueCreate(CANRX_QUEUE_LEN, sizeof(CanRxMsg));
    if(xCANRcvQueue == NULL)
    {
      printf("CANRcvQueue create failed");
      return;                                    //�������ն���ʧ��
    }
  }

  /* �������� */
  xReturn = xTaskCreate(CANSend_Task, "CANSend_Task", CANTX_STACK_SIZE, NULL, CANTX_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    printf("CANSend_Task create failed");
    return;                                      //������������ʧ��
  }

  xReturn = xTaskCreate(CANRcv_Task, "CANRcv_Task", CANRX_STACK_SIZE, NULL, CANRX_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    printf("CANRcv_Task create failed");
    return;                                      //������������ʧ��
  }
}

/************************************************
�������� �� CANSend_Date
��    �� �� CAN��������
��    �� �� TxMsg --- ����(CAN)��Ϣ
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void CANSend_Data(CanTxMsg TxMsg)
{
  if(xQueueSend(xCANSendQueue, &TxMsg, 100) != pdPASS)
  {                                              //�������ʧ��
    printf("CANSendQueue failed");
  }
}

/************************************************
�������� �� CANSend_Task
��    �� �� CAN����Ӧ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
static void CANSend_Task(void *pvParameters)
{
  static CanTxMsg TxMsg;

  for(;;)
  {
    /* �ȴ�������Ч���ݰ� */
    if(xQueueReceive(xCANSendQueue, &TxMsg, pdMS_TO_TICKS(10)) == pdTRUE)
    {
      if(CAN_Transmit(CANx, &TxMsg) == CAN_NO_MB)
      {
        vTaskDelay(1);                           //��һ�η���ʧ��, ��ʱ1���δ�, �ٴη���
        CAN_Transmit(CANx, &TxMsg);
      }
    }
  }
}

/************************************************
�������� �� CANRcv_DataFromISR
��    �� �� CAN��������
��    �� �� RxMsg --- ��������(����)
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void CANRcv_DataFromISR(CanRxMsg *RxMsg)
{
  static portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

  if(NULL != xCANRcvQueue)
  {
    xQueueSendFromISR(xCANRcvQueue, RxMsg, &xHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
  }
}

/************************************************
�������� �� CANRcv_Task
��    �� �� CAN����Ӧ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
static void CANRcv_Task(void *pvParameters)
{
  static CanRxMsg RxMsg;
  static Message msg;

  uint8_t i = 0;

  for(;;)
  {
    if(xQueueReceive(xCANRcvQueue, &RxMsg, pdMS_TO_TICKS(10)) == pdTRUE)
    {
      msg.cob_id = RxMsg.StdId;                  //CAN-ID

      if(CAN_RTR_REMOTE == RxMsg.RTR)
        msg.rtr = 1;                             //Զ��֡
      else
        msg.rtr = 0;                             //����֡

      msg.len = (UNS8)RxMsg.DLC;                 //����

      for(i=0; i<RxMsg.DLC; i++)                 //����
        msg.data[i] = RxMsg.Data[i];

      TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, DISABLE);
      canDispatch(&TestMaster_Data, &msg);       //����Э����ؽӿ�
      TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, ENABLE);
    }
  }
}

/********************************** CANOpen�ӿں���(���Լ�ʵ��) **********************************/
/************************************************
�������� �� canSend
��    �� �� CAN����
��    �� �� notused --- δʹ�ò���
            m --------- ��Ϣ����
�� �� ֵ �� 0:ʧ��  1:�ɹ�
��    �� �� strongerHuang
*************************************************/
unsigned char canSend(CAN_PORT notused, Message *m)
{
  uint8_t i;
  static CanTxMsg TxMsg;
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

  TxMsg.StdId = m->cob_id;

  if(m->rtr)
      TxMsg.RTR = CAN_RTR_REMOTE;
  else
      TxMsg.RTR = CAN_RTR_DATA;

  TxMsg.IDE = CAN_ID_STD;
  TxMsg.DLC = m->len;
  for(i=0; i<m->len; i++)
      TxMsg.Data[i] = m->data[i];

  /* �ж��Ƿ���ִ���ж� */
  if(0 == __get_CONTROL())
  {
    if(xQueueSendFromISR(xCANSendQueue, &TxMsg, &xHigherPriorityTaskWoken) != pdPASS)
    {                                            //�������ʧ��
      return 0xFF;
    }
    portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
  }
  else
  {
    if(xQueueSend(xCANSendQueue, &TxMsg, 100) != pdPASS)
    {                                            //�������ʧ��
      return 0xFF;
    }
  }

  return 0;
}

/************************************************
�������� �� setTimer
��    �� �� Set the timer for the next alarm.
��    �� �� value --- ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void setTimer(TIMEVAL value)
{
  uint32_t timer = TIM_GetCounter(CANOPEN_TIMx); // Copy the value of the running timer

  elapsed_time += timer - last_counter_val;
  last_counter_val = CANOPEN_TIM_PERIOD - value;
  TIM_SetCounter(CANOPEN_TIMx, CANOPEN_TIM_PERIOD - value);
  TIM_Cmd(CANOPEN_TIMx, ENABLE);
}

/************************************************
�������� �� getElapsedTime
��    �� �� Return the elapsed time to tell the Stack how much time is spent since last call.
��    �� �� ��
�� �� ֵ �� (���ŵ�)ʱ��
��    �� �� strongerHuang
*************************************************/
TIMEVAL getElapsedTime(void)
{
  uint32_t timer = TIM_GetCounter(CANOPEN_TIMx); // Copy the value of the running timer

  if(timer < last_counter_val)
    timer += CANOPEN_TIM_PERIOD;

  TIMEVAL elapsed = timer - last_counter_val + elapsed_time;

  return elapsed;
}

/************************************************
�������� �� TIMx_DispatchFromISR
��    �� �� ��ʱ����(�Ӷ�ʱ���ж�)
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void TIMx_DispatchFromISR(void)
{
  last_counter_val = 0;
  elapsed_time = 0;
  TimeDispatch();
}


/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
